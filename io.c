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
	int ret;
	char buffer[4092];

	unlink("nufile");
	fd = creat("nufile", 666);
	if (fd == -1)
		printf("could not create file\n");
	fd = open("nufile", O_RDWR);
	write(fd, "Hello World\n", 13);
	close(fd);
	fd = open("nufile", O_RDWR);
	ret = read(fd, buffer, 14);
	close(fd);
	printf("%d[%s]\n", ret, buffer);
	return 0;
}
