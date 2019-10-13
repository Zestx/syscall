#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>

int	exec_ls(char *options)
{
	pid_t PID = fork();
	if (PID < 0) {
		perror("error: forking failed: ");
		return (0);
	}
	
	if (PID) {
		wait(&PID);
	} else {
		execl("/bin/ls", "ls", options, NULL);
	}
	return (1);
}

int	main(void)
{
	int fd;

	exec_ls("-l");
	creat("new_file", 644);
	exec_ls("-l");
	unlink("new_file");
	exec_ls("-l");
	creat("new_file", 7000);
	exec_ls("-l");
	unlink("new_file");
	creat("../new_file", 0);
	return 0;
}
