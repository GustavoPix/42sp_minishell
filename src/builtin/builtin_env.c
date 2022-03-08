// trocar header depois.

#include "../cmds/cmds.h"

void	builtin_env(t_cmd *builtin, int fd[], char *envp[])
{
	int		i;

	i = 0;
	(void)builtin;
	while (envp[i])
	{
		write(fd[1], envp[i], ft_strlen(envp[i]));
		write(fd[1], "\n", 1);
		i++;
	}
}
