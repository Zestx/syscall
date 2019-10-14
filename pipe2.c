#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define MSG_SIZE 13

int	main(void)
{
	int	p[2];
	pid_t	child_pid;

	if (pipe(p) < 0) {
		perror("pipe error: ");
		exit(EXIT_FAILURE);
	}

	child_pid = fork();
	if (child_pid < 0) {
		perror("forking failed: ");
		exit(EXIT_FAILURE);
	}
	if (child_pid > 0) {
		write(p[1], "Hello Child!", MSG_SIZE);
		write(p[1], "How u doing?", MSG_SIZE);
		close(p[1]);
		wait(NULL);
	}
	if (child_pid == 0) {
		close(p[1]);
		char buff[MSG_SIZE];
		while (read(p[0], buff, MSG_SIZE) > 0)
			printf("[%s]\n", buff);
	}
	return 0;
}
