// trocar header depois.

#include "../cmds/cmds.h"


// sempre que atualizarmos o cd atual, também atualizar o OLDPWD.
void	builtin_cd(t_cmd *builtin, int fd[])
{
	int		chreturn;

	(void)fd;
	if ((builtin->parans[1] == NULL || strncmp(builtin->parans[1], "~", 1) == 0))
		chreturn = chdir(getenv("HOME"));
	else if (strncmp(builtin->parans[1], "-", 1) == 0)
		chreturn = chdir(getenv("OLDPWD"));
	else if (strncmp(builtin->parans[1], ".", 1) == 0)
		chreturn = chdir(".");
	else if (strncmp(builtin->parans[1], "..", 2) == 0)
		chreturn = chdir("..");
	else
		chreturn = chdir(builtin->parans[1]);
	if (chreturn == -1)
	{
		fprintf(stderr,"cd: %s: No such file or directory\n",builtin->parans[1]);
	}

}
