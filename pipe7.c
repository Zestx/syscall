#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

#define	RDBUFF_SIZE 4092

int	execute_cmd(char ***cmd_list, int idx, int limit, int read_fd);
void	err_handler(char *err_msg);
void	print_pipe(int p_out);

//=======================================================
//pipelining an arbitrary number of processes together
//using recursion.
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
	char ***cmd_list;
	int i = 0;

	//getting the list of the programs to run and their args
	if (argc == 1)
		return 0;
	cmd_list = malloc(sizeof(cmd_list) * argc - 1);
	while (i < argc) {
		cmd_list[i] = ft_strsplit(argv[i + 1], ' ');
		i++;
	}
	//executing the programs and pipelining them recursively,
	//then printing the last one's output on stdout.
	print_pipe(execute_cmd(cmd_list, 0, argc - 1, 0));
	return 0;
}

//core function
int	execute_cmd(char ***cmd_list, int idx, int limit, int read_fd)
{
	pid_t	child_pid;
	int	p[2];

	//stop recursion if last program has been executed
	if (idx == limit)
		return read_fd;
	//creating the pipe and forking
	if (pipe(p) < 0)
		err_handler("pipe error: ");
	if ((child_pid = fork()) < 0)
		err_handler("fork error: ");
	//parent just close the write-end of the pipe
	if (child_pid) {
		close(p[1]);
	//child remap stdin to the the read_fd,
	//which is just stdin on the first call
	} else {
		close(p[0]);
		dup2(read_fd, STDIN_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execvp(cmd_list[idx][0], cmd_list[idx]);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
	//calling execute_cmd on the next program, sending it
	//the read-end of our pipe as its read_fd
	return execute_cmd(cmd_list, ++idx, limit, p[0]);
}

//read the content of a pipe
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
