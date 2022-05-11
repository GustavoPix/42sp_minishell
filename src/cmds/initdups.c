/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:36:07 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/10 21:12:57 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initdups(t_data *data, t_cmd *cmd, int fd[])
{
	if (cmd->fd_file_in)
	{
		if (cmd->fd_file_in == -1)
		{
			ft_putstr_fd(cmd->file_in, 1);
			ft_putstr_fd(":No such file or directory\n", 1);
			exit(1);
		}
		else
			dup2(cmd->fd_file_in, STDIN_FILENO);
	}
	else
		dup2(data->fd, STDIN_FILENO);
	not_pipe_cmds(data, cmd);
	if (cmd->fd_file_out)
		dup2(cmd->fd_file_out, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
}
