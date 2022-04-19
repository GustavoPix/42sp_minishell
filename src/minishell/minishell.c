/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:12:08 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/04/19 20:41:49 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_minishell(t_data *data)
{
	close(data->fd);
	if (data->cmds->file_in)
		close(data->cmds->fd_file_in);
	clear_inputline(data->i_line);
	clear_cmds(data->cmds, 1);
	clear_envs(data);
	ft_putstr_fd("Bye! ;)\n", 1);
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
			break;
		else if (data->cmds->file_out)
			write(data->cmds->fd_file_out, buffer, ft_strlen(buffer));
		else
			write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}

	// alterar Dprintf depos
	while (i < data->cmds->qty)
	{
		if (temp->error == 0)
			dprintf(2,"command not found: %s\n", temp->bin);
		i++;
		if (i < data->cmds->qty)
			temp = temp->next;
	}
	clear_cmds(data->cmds, 0);
	return (0);
}

int	execute_minishell(t_data *data)
{
	t_cmd	*temp;
	int		i;
	int		exit_code;

	temp = data->cmds->first_cmd;
	i = 0;
	while (i < data->cmds->qty)
	{
		if (temp->error == 1)
			exit_code = execute_cmds(data, temp, i);
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

int	loop_minishell(t_data *data)
{
	while (strcmp(data->i_line->input, "exit") != 0)
	{
		read_minishell(data);
		debug_cmds(data->cmds);
		data->exit_code =  execute_minishell(data);
		output_minishell(data);
	}
	exit_minishell(data);
	return (0);
}
