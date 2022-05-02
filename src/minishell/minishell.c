/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:12:08 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/02 20:40:39 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../signals/signals.h"

int	exit_minishell(t_data *data)
{
	close(data->fd);
	// lembrar de limpar os fd's de todos os comandos (dentro do clear);
	// if (data->cmds->file_in)
	// 	close(data->cmds->fd_file_in);
	clear_inputline(data->i_line);
	clear_cmds(data->cmds, 1);
	clear_envs(data);
	return (0);
}

int	output_minishell(t_data *data)
{
	char	*buffer;
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = data->cmds->first_cmd;
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
	while (i < data->cmds->qty)
	{
		if (temp->error == 0)
			printf("command not found: %s\n", temp->bin);
		i++;
		if (i < data->cmds->qty)
			temp = temp->next;
	}
	clear_cmds(data->cmds, 0);
	return (0);
}

int	execute_minishell(t_data *data, t_action *action)
{
	t_cmd	*temp;
	int		i;
	int		exit_code;

	temp = data->cmds->first_cmd;
	i = 0;
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
		read_minishell(data);
		debug_cmds(data->cmds);
		data->exit_code = execute_minishell(data, action);
		output_minishell(data);
	}
	exit_minishell(data);
	return (0);
}
