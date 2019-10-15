#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//piping three processes together

void	err_report_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int 	main(void)
{
	int p1[2], p2[2];
	pid_t ls_pid, grep_pid, less_pid;

	if (pipe(p1) < 0 || pipe(p2) < 0)
		err_report_exit("pipe error: ");
	//ls
	if ((ls_pid = fork()) < 0)
		err_report_exit("ls fork error: ");
	if (ls_pid) {
		close(p1[1]);
	}
	if (!ls_pid) {
		dup2(p1[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execlp("ls", "ls", "-l", NULL);
	}
	//grep
	if ((grep_pid = fork()) < 0)
		err_report_exit("grep fork error: ");
	if (grep_pid) {
		close(p1[1]);
	}
	if (!grep_pid) {
		dup2(p1[0], STDIN_FILENO);
		dup2(p2[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execlp("grep", "grep", "\\.c", NULL);
	}
	//less
	if ((less_pid = fork()) < 0)
		err_report_exit("less fork error: ");
	if (less_pid) {
		close(p2[1]);
		waitpid(less_pid, NULL, 0);
	}
	if (!less_pid) {
		dup2(p2[0], STDIN_FILENO);
		close(p2[0]);
		close(p2[1]);
		execlp("less", "less", NULL);
	}
	return 0;
}
