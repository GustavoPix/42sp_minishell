#include "minishell.h"

void	builtin_cd(char	**comand, int fd[])
{
	char	*temp;
	char	*path;
	int		chreturn;

	(void)fd;
	if ((comand[1] == NULL || strncmp(comand[1], "~", 1) == 0))
		chreturn = chdir(getenv("HOME"));
	else if (strncmp(comand[1], "-", 1) == 0)
		chreturn = chdir(getenv("OLDPWD"));
	else if (strncmp(comand[1], ".", 1) == 0)
		chreturn = chdir(getenv("PWD"));
	else if (strncmp(comand[1], "..", 2) == 0)
	{
		path = ft_strdup(getenv("PWD"));
		temp = ft_strrchr(path, '/');
		*temp = '\0';
		chreturn = chdir(getenv("PWD"));
	}
	else
		chreturn = chdir(comand[1]);
	if (chreturn == -1)
	{
		fprintf(stderr,"cd: %s: No such file or directory\n",comand[1]);
	}
}
