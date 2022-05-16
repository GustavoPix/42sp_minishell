/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:12:08 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/16 16:59:49 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../signals/signals.h"

int	exit_minishell(t_data *data)
{
	close(data->fd);
	clear_inputline(data->i_line);
	clear_cmds(data->cmds, 1);
	clear_envs(data);
	return (0);
}

static void	output_minishell(t_data *data)
{
	char	*buffer;

	while (data->fd)
	{
		buffer = get_next_line(data->fd);
		if (buffer == NULL)
			break ;
		else if (data->cmds->last_cmd->file_out)
			write(data->cmds->last_cmd->fd_file_out, buffer, ft_strlen(buffer));
		else
			write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}
	treat_errors(data);
}

int	execute_minishell(t_data *data, t_action *action)
{
	t_cmd	*temp;
	int		i;
	int		exit_code;

	temp = data->cmds->first_cmd;
	i = 0;
	exit_code = 0;
	while (i < data->cmds->qty)
	{
		if (temp->error == 1)
			exit_code = execute_cmds(data, temp, action);
		i++;
		if (i < data->cmds->qty)
			temp = temp->next;
	}
	return (exit_code);
}

int	read_minishell(t_data *data)
{
	input_line(data);
	split_cmds(data->cmds, data->i_line->input);
	setup_cmds_bin_path(data);
	return (0);
}

int	loop_minishell(t_data *data, t_action *action)
{
	while (strcmp(data->i_line->input, "exit") != 0)
	{
		init_sigaction(&action->sigaction, handler_int, SIGINT);
		init_sigaction(&action->sigaction, SIG_IGN, SIGQUIT);
		data->fd = 0;
		read_minishell(data);
		data->exit_code = execute_minishell(data, action);
		output_minishell(data);
		clear_cmds(data->cmds, 0);
	}
	exit_minishell(data);
	return (0);
}
