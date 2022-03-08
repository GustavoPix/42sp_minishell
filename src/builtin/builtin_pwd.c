// trocar header depois.

#include "../cmds/cmds.h"

void	builtin_pwd(t_cmd *builtin, int fd[])
{
	char	pwd[255];

	(void)fd;
	(void)builtin;
	getcwd(pwd, sizeof(pwd));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}
