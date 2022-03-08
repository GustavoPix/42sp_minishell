// trocar header depois.

#include "../cmds/cmds.h"

void	builtin_echo(t_cmd *builtin, int fd[])
{
	// printf("Chegou aqui\n");
	// juntar todos os parametros caso existam.
	(void)fd;
	if (builtin->parans[1])
	{
		if (ft_strncmp(builtin->parans[1], "-n", ft_strlen("-n")) == 0)
		{
			printf("\n");
			write(1, builtin->parans[2], ft_strlen(builtin->parans[2] - 1));
		}
		else
		{
			printf("\n");
			ft_putstr_fd(builtin->parans[1], 1);
		}
	}
	ft_putchar_fd('\n', 1);
}
