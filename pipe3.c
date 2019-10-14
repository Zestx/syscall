#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//Setting a two-ways communication between father and child processes.
#define MSG_LEN	14
#define P_READ	ptop[0]
#define C_WRITE ptop[1]

int	main(void) 
{
	//We declare create two pipes because we need a two-way communications.
	int	ptop[2];
	if (pipe(ptop) < 0) {
		perror("pipe error: ");
		exit(EXIT_FAILURE);
	}
	//we fork our process
	pid_t child_pid;
	if ((child_pid = fork()) < 0) {
		perror("fork error: ");
		exit(EXIT_FAILURE);
	}
	if (child_pid > 0) {
		//We read the from the 'ptop' pipe, so we should
		//get the standard output of the child.
		close(C_WRITE);
		char rd_buff[14];
		wait(&child_pid);
		while (read(P_READ, rd_buff, MSG_LEN) > 0)
			printf("MESSAGE: [%s]\n", rd_buff);
	} else {
		//We're remapping the stdout of our child process to 
		//the write-end of the 'ptop' pipe. We then want to close
		//the two ends of the pipe because we don't need to
		//read from it (this is for the other/father process)
		//and don't want to write in it other than with the
		//standard output of the program.
		dup2(C_WRITE, STDOUT_FILENO);
		close(P_READ);
		close(C_WRITE);
		printf("Hello, Parent!");
		printf("How you doing?");
	}
	return 0;
}
