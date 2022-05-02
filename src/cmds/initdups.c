/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:36:07 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/02 20:16:57 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initdups(t_data *data, t_cmd *cmd, int fd[])
{
	dup2(data->fd, STDIN_FILENO);
	if (cmd->fd_file_in)
		dup2(cmd->fd_file_in, STDIN_FILENO);
	not_pipe_cmds(data, cmd);
	dup2(fd[1], STDOUT_FILENO);
	if (cmd->fd_file_out)
		dup2(cmd->fd_file_out, STDOUT_FILENO);
}
