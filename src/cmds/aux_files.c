/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:46:33 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/19 22:09:22 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "../minishell.h"
#include "../signals/signals.h"

int	not_pipe_cmds(t_data *data, t_cmd *cmd)
{
	(void)data;
	if ((ft_strncmp(cmd->bin, "/usr/bin/ls", ft_strlen(cmd->bin)) == 0)
		&& cmd->parans[1] == NULL && cmd->fd_file_out == 0
		&& data->cmds->qty == 1)
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
		else if (ft_strncmp(cmd->bin, "exit", ft_strlen(cmd->bin)) == 0
			&& data->cmds->qty == 1)
			builtin_exit(data, cmd);
		else
			return (1);
		return (0);
	}
	return (1);
}

int	ft_fdjoin(int fd1, int fd2)
{
	char	*buffer;

	while (1)
	{
		buffer = get_next_line(fd1);
		if (buffer == NULL)
		{
			break ;
		}
		write(fd2, buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (0);
}
