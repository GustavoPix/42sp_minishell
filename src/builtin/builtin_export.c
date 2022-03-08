// trocar header depois.

#include "../cmds/cmds.h"
// lembrar de dar join nos parans;

void	builtin_export(t_cmd *builtin, int fd[], char *envp[])
{
	int		size_env;
	char	*variable_export;

	(void)fd;
	size_env = 0;
	while(envp[size_env])
		size_env++;
	variable_export = ft_strchr(builtin->parans[1], '=');
	variable_export++;
	envp[size_env] = variable_export;
	envp++[size_env] = NULL;
}
