/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:36:07 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/04/11 20:03:43 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initdups(t_data *data, t_cmd *cmd, int fd[])
{
	dup2(data->fd, STDIN_FILENO);
	if (data->cmds->fd_file_in)
		dup2(data->cmds->fd_file_in, STDIN_FILENO);
	not_pipe_cmds(data, cmd);
	dup2(fd[1], STDOUT_FILENO);
	if (data->cmds->fd_file_out)
		dup2(data->cmds->fd_file_out, STDOUT_FILENO);
}
