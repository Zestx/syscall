#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFF_SIZE 4092

//redirecting the output of a program ('cat' here)
//to the stdin of another program ('grep' here)
//DOESN'T WORK
void	err_handler(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	//creating a pipe to communicate between the child processes
	int	p[2];
	if (pipe(p) < 0)
		err_handler("pipe error: ");
	/*
	** forking for cat
	*/
	pid_t cat_pid;
	if ((cat_pid = fork()) < 0)
		err_handler("fork error: ");
	if (cat_pid) {
		close(p[1]);
	}
	if (!cat_pid) {
		printf("===CAT===\n");
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		execl("/bin/cat", "cat", "pipe4.c", NULL);
		exit(EXIT_SUCCESS);
	}
	/*
	** forking for grep
	*/
	pid_t grep_pid;
	if ((grep_pid = fork()) < 0)
		err_handler("fork_error: ");
	if (grep_pid)
		wait(&grep_pid);
	if (!grep_pid) {
		printf("===GREP===\n");
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		execl("/bin/grep", "grep", "\"err_handler\"", NULL);
		exit(EXIT_SUCCESS);
	}
	return 0;
}
