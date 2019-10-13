#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int	p[2];
	char	buff[15];

	if (pipe(p) < 0) {
		perror("pipe error: ");
		exit(EXIT_FAILURE);
	}
	write (p[1], "Hello Pipe! #1", 15);
	write (p[1], "Hello Pipe! #2", 15);
	write (p[1], "Hello Pipe! #3", 15);
	for (int i = 0; i < 3; i++) {
		read(p[0], buff, 15);
		printf("MESSAGE: %s\n", buff);
	}
	return 0;
}
