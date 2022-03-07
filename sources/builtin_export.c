#include "minishell.h"

void	builtin_export(char **comand, int fd[], char *envp[])
{
	int		size_env;
	char	*variable_export;

	(void)fd;
	size_env = 0;
	while(envp[size_env])
		size_env++;
	variable_export = ft_strchr(*comand, '=');
	variable_export++;
	envp[size_env] = variable_export;
	envp++[size_env] = NULL;
}
