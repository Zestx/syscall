#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"
//pipelining an arbitrary number of processes together.
//it implies that the fork/execute part needs to be in 
//a separate function to be called an arbitrary number
//of times.
//The processes are recieved as arguments to the program,
//each strings representing the program path and it's
//arguments separated by whitespaces.
void	err_handler(char *err_msg);
void	execute_cmd(char *path, char **args, char **env);
//!\	by now this is a dirty implementation without input or error checks.
//!\	The goal is just to practice pipelining.
int	main(int argc, char **argv)
{
	extern char **environ;
	//we first get all the commands and separate them into arguments
	//everything is stocked in cmd_list
	char ***cmd_list;
	cmd_list = malloc(sizeof(cmd_list) * argc + 1);
	int i = 1;
	while (i - 1 < argc) {
		cmd_list[i - 1] = ft_strsplit(argv[i], ' ');
		i++;
	}
	//executing the programs one by one (no pipes yet)
	i = 0;
	while (i < argc - 1) {
		execute_cmd(cmd_list[i][0], cmd_list[i], environ);
		i++;
	}
	return 0;
}

void	execute_cmd(char *path, char **args, char **env)
{
	pid_t child_pid;

	if ((child_pid = fork()) < 0)
		err_handler("fork error: ");
	if (child_pid) {
		waitpid(child_pid, NULL, 0);
	} else {
		execve(path, args, env);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
}

void	err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
