/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe7-rev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:26:57 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/28 19:34:52 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void execute(char **cmd_args)
{
	execvp(cmd_args[0], cmd_args);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

static void	execute_first(char **cmd_args)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_handler("fork error: ");
	else if (pid == 0)
		execute(cmd_args);
	else if (pid > 0)
		wait(&pid);
}

static int execute_cmd(char ***cmd_list, int idx)
{
	pid_t	pid;
	int	p[2];

	if (!idx)
	{
		execute_first(cmd_list[0]);
		return -1;
	}
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
		execute_cmd(cmd_list, idx--);
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
	pid = execute_cmd(cmd_list, argc - 2);
	waitpid(pid, &status, 0);
	return 0;
}
