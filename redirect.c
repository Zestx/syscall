#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFF_SIZE 4092

//redirecting the output of a program ('ls' here) into an exeternal file.
void	err_handler(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	//we create a pipe
	int	ptop[2];
	if (pipe(ptop) < 0)
		err_handler("pipe error: ");
	//we fork our process
	pid_t child_pid;
	if ((child_pid = fork()) < 0)
		err_handler("fork error: ");
	//parent process
	if (child_pid) {
		wait(&child_pid);
		//closing unused fds and creating our output file
		close(ptop[1]);
		if (creat("ls_output", 644) < 0)
			err_handler("creat error: ");
		//read the output of the ls
		//(executed in the child, which's output has been redirected
		//to the 'ptop' pipe we're reading from) 
		//and writing it to an external file (ls_output)
		int	ls_fd = open("./ls_output", O_WRONLY);
		char	rd_buff[4092];
		int	rd_len;
		while((rd_len = read(ptop[0], rd_buff, 4092)) != 0) {
			if (rd_len < 0)
				err_handler("read error: ");
			if (write(ls_fd, rd_buff, rd_len) < 0)
				err_handler("write error: ");
		}
		close(ls_fd);
	}
	//child process
	if (!child_pid) {
		//redirecting stdout to the ptop 'pipe in' and closing unused fds
		dup2(ptop[1], STDOUT_FILENO);
		close(ptop[0]);
		close(ptop[1]);
		//executing 'ls'
		execl("/bin/ls", "ls", "-l", "/home/pom", NULL);
	}
	return 0;
}
