/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:57:03 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/03/30 22:11:34 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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

int main(int argc, char **argv, char **env)
{
	t_data data;
	t_cmd *temp;
	int		exit_code;
	int		i;

	(void)argc;
	(void)argv;
	(void)env;
	clear();
	data.i_line = start_inputline();
	data.cmds = start_cmds();
	start_envs(&data, env);
	while (strcmp(data.i_line->input, "exit") != 0)
	{
		// show_path(data.i_line);
		input_line(&data);
		split_cmds(data.cmds, data.i_line->input);
		setup_cmds_bin_path(&data);
		debug_cmds(data.cmds);
		i = 0;
		temp = data.cmds->first_cmd;
		while (i < data.cmds->qty)
		{
			exit_code = execute_cmds(&data, temp, i);
			i++;
			if (i < data.cmds->qty)
				temp = temp->next;
		}
		char	*buffer;
		while (1)
		{
			buffer = get_next_line(data.fd);
			if (buffer == NULL)
				break;
			if (data.cmds->file_out)
				write(data.cmds->fd_file_out, buffer, ft_strlen(buffer));
			else
				write(1, buffer, ft_strlen(buffer));
			free(buffer);
		}
		if (data.cmds->file_out)
			close(data.cmds->fd_file_out);
		clear_cmds(data.cmds, 0);
	}
	close(data.fd);
	if (data.cmds->file_in)
		close(data.cmds->fd_file_in);
	//close(0);
	//close(3);
	//close(2);
	//close(1);
	//close(4);
	clear_inputline(data.i_line);
	clear_cmds(data.cmds, 1);
	clear_envs(&data);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
