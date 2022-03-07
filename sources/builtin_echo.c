#include "minishell.h"

void	builtin_echo(char **comand, int fd[])
{
	/* em caso de -n */
	/*
	if (-n)
		write(fd[1], comand[1], ft_strlen(comand[1]) - 1);
		write(fd[1], "\n", 1);
	*/
	if (comand[0])
	{
		write(fd[1], comand[1], ft_strlen(comand[1]));
		write(fd[1], "\n", 1);
	}
	write(fd[1], "\n", 1);
}
