/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:12:08 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/03/31 20:35:16 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void setup_cmds_bin_path(t_data *data)
{
	t_cmd *cmd;
	int i;

	i = 0;
	cmd = data->cmds->first_cmd;
	while (i < data->cmds->qty)
	{
		test_and_apply_bin(data, cmd);
		i++;
		if (i < data->cmds->qty)
			cmd = cmd->next;
	}
}


// int	free_minishell(t_data *data)
// {

// }

int	output_minishell(t_data *data)
{
	char	*buffer;

	while (1)
	{
		buffer = get_next_line(data->fd);
		if (buffer == NULL)
			break;
		if (data->cmds->file_out)
			write(data->cmds->fd_file_out, buffer, ft_strlen(buffer));
		else
			write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}
	if (data->cmds->file_out)
		close(data->cmds->fd_file_out);
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
		//debug_cmds(data.cmds);
		execute_minishell(data);
		output_minishell(data);
		//free_minishell(data);
	}
	return (0);
}
