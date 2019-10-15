#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

#define	RDBUFF_SIZE 2

void	err_handler(char *err_msg);
void	execute_cmd(char *path, char **args, int p[2]);

//======================================================
//pipelining an arbitrary number of processes together.
//it implies that the fork/execute part needs to be in 
//a separate function to be called an arbitrary number
//of times.
//The processes are recieved as arguments to the program,
//each strings representing the program path and it's
//arguments separated by whitespaces.
//------------------------------------------------------
//!\ dirty implementations without input/error checking
//!\ goal is just to learn pipelining.
//------------------------------------------------------
//======================================================
int	main(int argc, char **argv)
{
	//we first get all the commands and separate them into arguments
	char ***cmd_list;
	cmd_list = malloc(sizeof(cmd_list) * argc + 1);
	int i = 1;
	while (i - 1 < argc) {
		cmd_list[i - 1] = ft_strsplit(argv[i], ' ');
		i++;
	}
	//creating our pipe
	//executing the programs one by one and pipelining them
	i = 0;
	char *f_out = ft_strdup("");
	while (i < argc - 1) {
		//creating a new pipe
		int p[2];
		if (pipe(p) < 0)
			err_handler("pipe error: ");
		//writing the output of the last program (or "" if first iteration) into the pipe-in
		write(p[1], f_out, ft_strlen(f_out));
		//executing the command, sending it the pipe's fds
		execute_cmd(cmd_list[i][0], cmd_list[i], p);
		//reading the command output into tmp
		char rd_buff[RDBUFF_SIZE] = {0};
		char *tmp = ft_strdup("");
		while (read(p[0], rd_buff, RDBUFF_SIZE) > 0)
			tmp = ft_strjoin(tmp, rd_buff);
		//closing the pipe
		close(p[0]);
		close(p[1]);
		//copying tmp into f_out
		f_out = ft_strdup(tmp);
		i++;
	}
	if (f_out[0])
		printf("%s", f_out);
	return 0;
}

void	execute_cmd(char *bin, char **args, int p[2])
{
	pid_t child_pid;
	if ((child_pid = fork()) < 0)
		err_handler("fork error: ");
	if (child_pid) {
		close(p[1]);
	} else {
		dup2(p[0], STDIN_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		execvp(bin, args);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
}

void	err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
