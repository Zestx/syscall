#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

#define IN 1
#define OUT 0

//=======================================================
//Pipelining an arbitrary number of processes together.
//using recursion.

//Usage:
//	$> ./pl "prog_0 arga" "prog_1" "prog_2 arga argb"
//will behave like
//	$> prog_0 arga | prog_1 | prog_2 arga argb
//-------------------------------------------------------

static int err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

static void execute(char **cmd_list)
{
	execvp(cmd_list[0], cmd_list);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

static int execute_cmd(char ***cmd_list, int idx)
{
	pid_t	pid;
	int	p[2];

	if (!idx--)
		return -1;
	if (pipe(p) < 0)
		err_handler("pipe error: ");
	if ((pid = fork()) < 0)
		err_handler("fork error: ");
	else if (pid == 0)
	{
		close(p[IN]);
		dup2(p[OUT], STDIN_FILENO);
		close(p[OUT]);
		execute(cmd_list[idx]);
	}
	else if (pid > 0) 
	{
		close(p[OUT]);
		dup2(p[IN], STDOUT_FILENO);
		close(p[IN]);
		execute_cmd(cmd_list, idx);
	}
	return pid;
}

int main(int argc, char **argv)
{
	char ***cmd_list;
	int pid;
	int i = 0;
	int status;

	if (argc == 1)
		return 0;
	cmd_list = malloc(sizeof(cmd_list) * argc - 1);
	while (i < argc)
	{
		cmd_list[i] = ft_strsplit(argv[i + 1], ' ');
		i++;
	}
	pid = execute_cmd(cmd_list, argc - 1);

	ssize_t n;
	char buff[4096];

	while ((n = read(0, buff, 4096)) > 0)
		write(1, buff, n);
	close(1);
	waitpid(pid, &status, 0);
	return 0;
}
