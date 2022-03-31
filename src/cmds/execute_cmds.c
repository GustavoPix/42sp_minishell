/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:12:45 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/30 22:11:28 by glima-de         ###   ########.fr       */
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
	else if (ft_strncmp(builtin->bin, "unset", ft_strlen("unset")) == 0)
		builtin_unset(data, builtin, fd);
	else if (ft_strncmp(builtin->bin, "env", ft_strlen("env")) == 0)
		builtin_env(data, builtin, fd);
	else if (ft_strncmp(builtin->bin, "exit", ft_strlen("exit")) == 0)
		exit(0);
}

int	execute_cmds(t_data *data, t_cmd *cmd, int i)
{
	int	fd[2];
	int	pid;
	int	exit_code;

	(void)i;
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(data->fd, STDIN_FILENO);
		if (data->cmds->fd_file_in)
			dup2(data->cmds->fd_file_in, STDIN_FILENO);
		if (cmd->bultin == 1)
			indentify_builtin(data, cmd, fd);
		else
		{
			// if ((cmd->document) == 1)
			// {
			// 	execute_doc(fd, "end");
			// 	dup2(fd[0], STDIN_FILENO);
			// }
			dup2(fd[1], STDOUT_FILENO);
			execve(cmd->bin, cmd->parans, NULL);
		}
		close(fd[1]);
		//close(3);
		//close(4);
		//close(5);
		//close(6);
		//close(7);
		//close(8);
		exit(0);
	}
	if (data->cmds->fd_file_in)
		data->cmds->fd_file_in = 0;
	if (data->fd)
		close(data->fd);
	data->fd = fd[0];
	waitpid(pid, &exit_code, 0);
	close(fd[1]);
	return (exit_code);
}
