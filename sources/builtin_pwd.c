#include "minishell.h"

void	builtin_pwd(char **comand, int fd[])
{
	char	pwd[PATH_MAX];

	(void)comand;
	getcwd(pwd, sizeof(pwd));
	write(fd[1], pwd, ft_strlen(pwd));
	write(fd[1], "\n", 1);
	free(pwd);
}
