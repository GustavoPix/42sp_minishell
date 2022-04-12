/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:12:45 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/11 21:29:33 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "../minishell.h"
#include <errno.h>

int	not_pipe_cmds(t_data *data, t_cmd *cmd)
{
	if ((ft_strncmp(cmd->bin, "/usr/bin/ls", ft_strlen(cmd->bin)) == 0)
		&& cmd->parans[1] == NULL && data->cmds->fd_file_out == 0)
	{
		if (execve(cmd->bin, cmd->parans, NULL) == -1)
			exit(1);
		exit(0);
	}
	return (1);
}

int	not_fork_cmds(t_data *data, t_cmd *cmd)
{
	if (cmd->bultin == 1)
	{
		if (ft_strncmp(cmd->bin, "cd", ft_strlen(cmd->bin)) == 0)
			builtin_cd(data, cmd);
		else if (ft_strncmp(cmd->bin, "export", ft_strlen(cmd->bin)) == 0)
			builtin_export(data, cmd);
		else if (ft_strncmp(cmd->bin, "unset", ft_strlen(cmd->bin)) == 0)
			builtin_unset(data, cmd);
		else
			return (1);
		return (0);
	}

	//else if (ft_strncmp(cmd->bin, "/usr/bin/ls", ft_strlen(cmd->bin)) == 0)
	//{
	//	if (data->cmds->qty == 1)
	//		if (execve(cmd->bin, cmd->parans, NULL) == -1)
	//			exit(1);
	//	return (0);
	//}

	return (1);
}

void	execute_doc(int fd[], char *end, t_data *data)
{
	char	*line;
	int		temp_file;
	int		stdin_fd_backup;

	stdin_fd_backup = dup(data->stdin_fd);
	temp_file = open("/tmp/here_doc_temp_file", O_CREAT | O_TRUNC | O_RDWR, 0777);
	while(1)
	{
		//ft_putstr_fd("-> ", 1);
		line = get_next_line(stdin_fd_backup);
		if (line == NULL)
			return ;
		else if (ft_strncmp(line, end, ft_strlen(line) - 1) == 0)
		{
			free((void *)line);
			close(stdin_fd_backup);
			close(temp_file);
			break ;
		}
		ft_putstr_fd(line, temp_file);
		free((void *)line);
	}
	fd[0] = open("/tmp/here_doc_temp_file", O_CREAT | O_RDWR, 0777);
}

void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[])
{

	if (ft_strncmp(builtin->bin, "echo", ft_strlen(builtin->bin)) == 0)
		builtin_echo(builtin, fd);
	else if (ft_strncmp(builtin->bin, "pwd", ft_strlen(builtin->bin)) == 0)
		builtin_pwd(builtin, fd);
	else if (ft_strncmp(builtin->bin, "env", ft_strlen(builtin->bin)) == 0)
		builtin_env(data, builtin, fd);
	else if (ft_strncmp(builtin->bin, "exit", ft_strlen(builtin->bin)) == 0)
		exit(0);
}

int	execute_cmds(t_data *data, t_cmd *cmd, int i)
{
	int	fd[2];
	int fake_fd[2];
	int	pid;
	int	exit_code;

	(void)i;
	if (not_fork_cmds(data, cmd) == 0)
		return (0);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		initdups(data, cmd, fd);
		//----
				//----
		if (cmd->bultin == 1)
		{
			if ((cmd->document) == 1)
			{
				pipe(fake_fd);
				execute_doc(fake_fd, cmd->doc_end, data);
				close(fake_fd[0]);
				close(fake_fd[1]);
			}
			indentify_builtin(data, cmd, fd);
		}
		else
		{
			if ((cmd->document) == 1)
			{
				execute_doc(fd, cmd->doc_end, data);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
			}
			//dup2(fd[1], STDOUT_FILENO);
			if (execve(cmd->bin, cmd->parans, NULL) == -1)
				exit(1);
		}
		close(data->cmds->fd_file_out);
		close(fd[1]);
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
