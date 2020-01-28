#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

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

static int err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

static void execute(char **cmd_list)
{
	execvp(cmd_list[0], cmd_list);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

//core function
static int execute_cmd(char ***cmd_list, int idx)
{
	pid_t	pid;
	int	p[2];

	//stop recursion if last program has been executed
	if (!idx--)
		return -1;

	//creating the pipe and forking
	if (pipe(p) < 0)
		err_handler("pipe error: ");
	if ((pid = fork()) < 0) {
		err_handler("fork error: ");
	} else if (pid == 0) {			// child
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		execute(cmd_list[idx]);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	} else if (pid > 0) {			// parent
		//parent just close the write-end of the pipe
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
		//calling execute_cmd on the next program, sending it
		//the read-end of our pipe as its fd
		execute_cmd(cmd_list, idx);
	}
	return pid;
}

int main(int argc, char **argv)
{
	char ***cmd_list;
	int status;
	int pid;
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
	pid = execute_cmd(cmd_list, argc - 1);

#if 1
{
	ssize_t n;
	char buff[4096];

	while ((n = read(0, buff, 4096)) > 0)
		write(1, buff, n);
	close(1);
}
#endif

	waitpid(pid, &status, 0);
	return status;
}
