#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
//forking a process
int	main(void)
{
	int x = 0;
	char args[][3] = {{"ls"}};

	//we fork our original process and check if all went well
	pid_t child_pid = fork();
	if (child_pid < 0) {
		perror("error: forking failed: ");
		return -1;
	}
	//fork returns 0 to the child, and the child's pid to the parent process. We use this to put
	//different codes in the father and in the child.
	if (child_pid) {
		//We're in the parent process. We're using wait(&pid) to wait for the child's code to
		//terminate before executing the rest of the code.
		printf("Parent process - my pid is %d and my child's pid is %d\n", getpid(), child_pid);
		wait(&child_pid);
		printf("Child process ended.\n");
	} else {
		//We're in the child process. We're replacing it with the "ls" executable using execl
		printf("Child process - my pid is %d and my mother's pid is %d\n", getpid(), getppid());
		execl("/bin/ls", "ls", "-l", "..", NULL);
	}
	return 0;
}
