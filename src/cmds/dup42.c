/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup42.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:36:07 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/04/08 21:21:36 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup42(t_data *data, int fd[])
{
	dup2(data->fd, STDIN_FILENO);
	if (data->cmds->fd_file_in)
		dup2(data->cmds->fd_file_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (data->cmds->fd_file_out)
		dup2(data->cmds->fd_file_out, STDOUT_FILENO);
}
