#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MSG_LEN 12


//Setting a one-way communication between father and child processes.
int	main(void)
{
	//We declare ptoc[2] which is gonna be a array containing the pipe's 
	//file descriptors (in and out) and then open a PIPE using the pipe() 
	//system call, which will asign a read-end to ptoc[0] and a write-end to ptoc[1]
	int	ptoc[2];
	if (pipe(ptoc) < 0) {
		perror("pipe error: ");
		exit(EXIT_FAILURE);
	}
	//We fork our process.
	pid_t	child_pid;
	if ((child_pid = fork()) < 0) {
		perror("fork error: ");
		exit(EXIT_FAILURE);
	}
	//The father process will write in the write-end of the file then close it.
	if (child_pid > 0) {
		write(ptoc[1], "Hello Child!", MSG_LEN);
		write(ptoc[1], "How u doing?", MSG_LEN);
		close(ptoc[1]);
		wait(NULL);
	}
	//The child process will close its write-end of the pipe, read in 
	//the read-end of the pipe, then print it on its stdout.
	if (child_pid == 0) {
		close(ptoc[1]);
		char p_buff[MSG_LEN];
		while (read(ptoc[0], p_buff, MSG_LEN) > 0)
			printf("[%s]\n", p_buff);
	}
	return 0;
}
