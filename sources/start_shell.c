#include "minishell.h"

char	*start_shell()
{
	char	*line;
	char	*user;
	char	dir[1024];

	user = getenv("USER");
	getcwd(dir, sizeof(dir));
	printf("\033[0;34m%s\033[0m in \033[0;33m%s\033[0m\n", user, dir);
	line = readline("> ");
	if (ft_strlen(line))
	{
		add_history(line);
		return (line);
	}
	return (NULL);
}
