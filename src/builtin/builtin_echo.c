// trocar header depois.

#include "../cmds/cmds.h"

void	builtin_echo(t_cmd *builtin, int fd[])
{
	char *aux;

	aux = ft_strdup(builtin->parans[1]);
	if (aux)
	{
		if (ft_strncmp(aux, "-n", ft_strlen("-n")) == 0)
		{
			write(fd[1], builtin->parans[2], ft_strlen(builtin->parans[2] - 1));
		}
		else
		{
			ft_putstr_fd(aux, fd[1]);
		}
	}
	ft_putchar_fd('\n', fd[1]);
	free(aux);
}
