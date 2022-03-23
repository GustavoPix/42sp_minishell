/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:12:45 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/22 20:57:51 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "../minishell.h"

void	execute_doc(int fd[], char *end)
{
	char	*line;

	while(1)
	{
		ft_putstr_fd("-> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, end, ft_strlen(line) - 1) == 0)
			{
				free((void *)line);
				close(0);
				close(1);
				close(fd[1]);
				break ;
			}
		ft_putstr_fd(line, fd[1]);
		free((void *)line);
	}
}

void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[])
{
	if (ft_strncmp(builtin->bin, "echo", ft_strlen("echo")) == 0)
		builtin_echo(builtin, fd);
	else if (ft_strncmp(builtin->bin, "cd", ft_strlen("cd")) == 0)
		builtin_cd(builtin, fd);
	else if (ft_strncmp(builtin->bin, "pwd", ft_strlen("pwd")) == 0)
		builtin_pwd(builtin, fd);
	else if (ft_strncmp(builtin->bin, "export", ft_strlen("export")) == 0)
		builtin_export(data, builtin, fd);
	//else if (ft_strncmp(builtin->bin, "unset", ft_strlen("unset")) == 0)
	//	builtin_unset(builtin, fd);
	else if (ft_strncmp(builtin->bin, "env", ft_strlen("env")) == 0)
		builtin_env(data, builtin, fd);
	else if (ft_strncmp(builtin->bin, "exit", ft_strlen("exit")) == 0)
		exit(0);
	// else
	// {
	// 	write(fd[1], "minishell: command not found: ", 31);
	// 	write(fd[1], builtin->bin, ft_strlen(builtin->bin));
	// 	write(fd[1], "\n", 1);
	// }
}

int	execute_cmds(t_data *data, t_cmd *cmd, int i)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		if (data->cmds->fd_file_in)
		{
			dup2(data->cmds->fd_file_in, STDIN_FILENO);
			data->cmds->fd_file_in = 0;
		}
		else if (i > 0)
			dup2(fd[0], STDIN_FILENO);

		if (cmd->bultin == 1)
			indentify_builtin(data, cmd, fd);
		else
		{
			// cmds->first_cmd->document = 1;
			// if ((cmd->document) == 1)
			// {
			// 	execute_doc(fd, "end");
			// 	dup2(fd[0], STDIN_FILENO);
			// }
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			execve(cmd->bin, cmd->parans, NULL);
		}
		close(fd[0]);
		close(fd[1]);
		// clear_cmds(cmd, 0);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	return (fd[0]);
}
