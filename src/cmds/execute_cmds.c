#include "cmds.h"

// achar um lugar melhor para essas duas funções;

void	indentify_builtin(t_cmd *builtin, int fd[])
{
	if (ft_strncmp(builtin->bin, "echo", ft_strlen("echo")) == 0)
		builtin_echo(builtin, fd);
	else if (ft_strncmp(builtin->bin, "cd", ft_strlen("cd")) == 0)
		builtin_cd(builtin, fd);
	else if (ft_strncmp(builtin->bin, "pwd", ft_strlen("pwd")) == 0)
		builtin_pwd(builtin, fd);
	// else if (ft_strncmp(builtin->bin, "export", ft_strlen("export")) == 0)
	// 	builtin_export(builtin, fd);
	// else if (ft_strncmp(builtin->bin, "unset", ft_strlen("unset")) == 0)
	// 	builtin_unset(builtin, fd);
	// else if (ft_strncmp(builtin->bin, "env", ft_strlen("env")) == 0)
	// 	builtin_env(builtin, fd);
	else if (ft_strncmp(builtin->bin, "exit", ft_strlen("exit")) == 0)
		exit(0);
	else
	{
		write(fd[1], "minishell: command not found: ", 31);
		write(fd[1], builtin->bin, ft_strlen(builtin->bin));
		write(fd[1], "\n", 1);
	}
}

int	execute_cmds(t_cmds *cmds)
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
		if (cmds->first_cmd->bultin == 1)
			indentify_builtin(cmds->first_cmd, fd);
		// else
		// {
		// 	dup2(cmds->file_in, STDIN_FILENO);
		// 	close(fd[0]);
		// 	dup2(cmds->file_out, STDOUT_FILENO);
		// 	if (execve(cmds->first_cmd->bin, cmds->first_cmd->parans, NULL) == -1)
		// 	{
		// 		// free aqui
		// 		// exit/return.
		// 	}
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	wait(NULL);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
