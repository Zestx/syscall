#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MSG_LEN 12

int	main(void)
{
	int	ptoc[2];
	if (pipe(ptoc) < 0) {
		perror("pipe error: ");
		exit(EXIT_FAILURE);
	}

	pid_t	child_pid;
	if ((child_pid = fork()) < 0) {
		perror("fork error: ");
		exit(EXIT_FAILURE);
	}
	if (child_pid > 0) {
		write(ptoc[1], "Hello Child", MSG_LEN);
		close(ptoc[1]);
		wait(NULL);
	}
	if (child_pid == 0) {
		close(ptoc[1]);
		char p_buff[MSG_LEN];
		read(ptoc[0], p_buff, MSG_LEN);
		printf("[%s]\n", p_buff);
	}
	return 0;
}
