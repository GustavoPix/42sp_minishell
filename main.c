/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:57:03 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/03/19 11:02:05 by wjuneo-f         ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	(void)env;
	data.i_line = start_inputline();
	data.cmds = start_cmds();
	start_envs(&data, env);
	while (strcmp(data.i_line->input, "exit") != 0)
	{
		// show_path(data.i_line);
		input_line(&data);
		split_cmds(data.cmds, data.i_line->input);
		setup_cmds_bin_path(&data);
		// debug_cmds(data.cmds);
		while (data.cmds->qty > 0)
		{
			execute_cmds(data.cmds);
			data.cmds->qty--;
		}
		clear_cmds(data.cmds, 0);
	}

	clear_inputline(data.i_line);
	clear_cmds(data.cmds, 1);
	clear_envs(&data);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
