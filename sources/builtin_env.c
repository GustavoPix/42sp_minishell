#include "minishell.h"

void	builtin_env(char **comand, int fd[], char *envp[])
{
	int		i;

	i = 0;
	(void)comand;
	while (envp[i])
	{
		write(fd[1], envp[i], ft_strlen(envp[i]));
		write(fd[1], "\n", 1);
		i++;
	}
}
