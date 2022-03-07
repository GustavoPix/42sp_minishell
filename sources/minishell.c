#include "minishell.h"

int	minishell(char *envp[])
{
	(void)envp;

	char	*line;
	char	**args;
	int		i;

	i = 0;
	line = start_shell();
	args = &line;
	printf("args = %s\n", args[0]);
	if (line)
	{
	// args = parsing_comands(line, envp);
		exec_comands(args, 2, envp);
	// free_ptr(args);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	clear();
	while(1)
	{
		minishell(envp);
	}
	return (0);
}
