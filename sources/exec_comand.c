#include "minishell.h"

// trocar strncmp para strcmp.
// aqui na verdade o comand[0] = comand[1]. Porque o 0 vai ser o path.
void	exec_builtin_child(char **comand, int fd[], char *envp[])
{
	if (ft_strncmp(comand[0], "echo", ft_strlen("echo")) == 0)
		builtin_echo(comand, fd);
	else if (ft_strncmp(comand[0], "cd", ft_strlen("cd")) == 0)
		builtin_cd(comand, fd);
	else if (ft_strncmp(comand[0], "pwd", ft_strlen("pwd")) == 0)
		builtin_pwd(comand, fd);
	else if (ft_strncmp(comand[0], "export", ft_strlen("export")) == 0)
		builtin_export(comand, fd, envp);
	else if (ft_strncmp(comand[0], "unset", ft_strlen("unset")) == 0)
		builtin_unset(comand, fd, envp);
	else if (ft_strncmp(comand[0], "env", ft_strlen("env")) == 0)
		builtin_env(comand, fd, envp);
	else if (ft_strncmp(comand[0], "exit", ft_strlen("exit")) == 0)
		exit(0);
	else
	{
		write(fd[1], "minishell: command not found: ", 31);
		write(fd[1], comand[1], ft_strlen(comand[1]));
		write(fd[1], "\n", 1);
	}
}

int	exec_comands(char	**comand, int indentify, char *envp[])
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		// if (indentify == 1) // se for um comando
		// 	exec_comands_child(comand, fd);
		if (indentify == 2) // se for uma builtin
			exec_builtin_child(comand, fd, envp);
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	return (0);
}
