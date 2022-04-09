/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup42.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:36:07 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/04/09 19:05:50 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup42(t_data *data, int fd[])
{
	if (data->cmds->fd_file_in)
		dup2(data->cmds->fd_file_in, STDIN_FILENO);
	else
		dup2(data->fd, STDIN_FILENO);
	if (data->cmds->fd_file_out)
	{
		dup2(data->cmds->fd_file_out, STDOUT_FILENO);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
}
