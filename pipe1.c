#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//setting a pipe and writing/reading from it in the same process
int	main(void)
{
	int	p[2];
	char	buff[15];
	//we set a pipe called 'p' and check for error
	if (pipe(p) < 0) {
		perror("pipe error: ");
		exit(EXIT_FAILURE);
	}
	//we write in the pipe 'in'
	write (p[1], "Hello Pipe! #1", 14);
	write (p[1], "Hello Pipe! #2", 14);
	write (p[1], "Hello Pipe! #3", 14);
	//we read from the pipe 'ou'
	for (int i = 0; i < 3; i++) {
		read(p[0], buff, 14);
		printf("MESSAGE: %s\n", buff);
	}
	return 0;
}
