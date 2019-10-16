#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFF_SIZE 4092

//redirecting the output of a program ('cat' here)
//to the stdin of another program ('grep' here)

void	err_handler(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	//creating a pipe to communicate between the child processes
	int	p1[2];
	if (pipe(p1) < 0)
		err_handler("pipe error: ");
	/*
	** forking for cat
	*/
	pid_t cat_pid;
	if ((cat_pid = fork()) < 0)
		err_handler("fork error: ");
	if (cat_pid) {
		//closing unused fds
		close(p1[1]);
	}
	if (!cat_pid) {
		//closing unused fds, rempaing stdout of the process
		//and executing cat
		dup2(p1[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		//no need for testing the return values for error, because
		//execl will only return in case of error, otherwise the
		//child will terminate and the following code wont be executed
		execl("/bin/cat", "cat", "pipe4.c", NULL);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
	/*
	** forking for grep
	*/
	pid_t grep_pid;
	if ((grep_pid = fork()) < 0)
		err_handler("fork_error: ");
	if (grep_pid)
		waitpid(grep_pid, NULL, 0);
	if (!grep_pid) {
		//closing unused fds, rempaing stdin of the process
		//to get inputs from cat and executing grep, which
		//is gonna output on "true" stdout.
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		close(p1[1]);
		execl("/bin/grep", "grep", "err_handler", NULL);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
	return 0;
}
