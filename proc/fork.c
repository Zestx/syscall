#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int x = 0;
	char args[][3] = {{"ls"}};

	pid_t fork_ret = fork();
	if (fork_ret < 0) {
		perror("error: forking failed: ");
		return -1;
	}
	if (fork_ret) {
		printf("Parent process - my pid is %d and my child's pid is %d\n", getpid(), fork_ret);
		wait(&fork_ret);
	} else {
		printf("Child process - my pid is %d and my mother's pid is %d\n", getpid(), getppid());
		execl("/bin/ls", "ls", "-l", "..", NULL);
	}
	return 0;
}
