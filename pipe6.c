#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

#define	RDBUFF_SIZE 4092

void	err_handler(char *err_msg);
void	execute_cmd(char *path, char **args, int p_read, int p_write);
void	print_pipe(int p_out);

//=======================================================
//pipelining an arbitrary number of processes together.
//The processes are recieved as arguments to the program:
//
//	$> ./pl "prog_0 arga" "prog_1" "prog_2 arga argb"
//will behave like
//	$> prog_0 arga | prog_1 | prog_2 arga argb
//
//-------------------------------------------------------
//!\ dirty implementations without input/error checking
//!\ goal is just to learn pipelining.
//-------------------------------------------------------
//=======================================================

int	main(int argc, char **argv)
{
	//getting all the commands and separatingg them into arguments
	char ***cmd_list;
	int i = 1;
	int join = 0;

	cmd_list = malloc(sizeof(cmd_list) * argc + 1);
	while (i - 1 < argc) {
		cmd_list[i - 1] = ft_strsplit(argv[i], ' ');
		i++;
	}
	//executing the programs 1 by 1 and pipelining them together
	i = 0;
	while (i < argc - 1) {
		int p[2];
		if (pipe(p) < 0)
			err_handler("pipe error: ");
		execute_cmd(cmd_list[i][0], cmd_list[i], join, p[1]);
		join = p[0];
		i++;
	}
	print_pipe(join);
	return 0;
}

void	execute_cmd(char *bin, char **args, int p_read, int p_write)
{
	pid_t child_pid;

	if ((child_pid = fork()) < 0)
		err_handler("fork error: ");
	if (child_pid) {
		waitpid(child_pid, NULL, 0);
		close(p_write);
	} else {
		dup2(p_read, STDIN_FILENO);
		dup2(p_write, STDOUT_FILENO);
		close(p_read);
		execvp(bin, args);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
}

void	print_pipe(int p_read)
{
	char rd_buff[RDBUFF_SIZE];

	while (read(p_read, rd_buff, RDBUFF_SIZE) > 0)
		printf("%s", rd_buff);
}

void	err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
