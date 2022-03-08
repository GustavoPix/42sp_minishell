// trocar header depois.

#include "../cmds/cmds.h"


// lembrar de dar join nos parans;
void	builtin_unset(t_cmd *builtin, int fd[], char *envp[])
{
	int		size_envp;
	int		size_temp;
	char	*variable_unset;
	char	**temp;

	(void)fd;
	variable_unset = ft_strchr(builtin->parans[1], '=');
	variable_unset++;
	size_envp = 0;
	while(envp[size_envp] != variable_unset)
		envp++;
	temp = ++envp;
	free(envp[size_envp]); // não sei se preciso dar free na variavel.
	size_temp = 0;
	while(temp[size_envp])
	{
		envp[size_envp] = temp[size_temp];
		size_temp++;
		size_envp++;
	}
	envp[size_envp] = NULL;
}
