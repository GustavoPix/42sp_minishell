/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:52:47 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/17 19:40:43 by wjuneo-f         ###   ########.fr       */
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
		if (data.cmds->qty == 1)
			if (ft_strncmp(data.cmds->first_cmd->bin, "cd", 2) == 0)
				gofolder(data.i_line, data.cmds->first_cmd->parans[1]);
		setup_cmds_bin_path(&data);
		// debug_cmds(data.cmds);
		if (data.cmds->qty > 0)
		{
			t_env *env_obj;
			env_obj = get_env(&data, data.cmds->first_cmd->bin);
			if (env_obj)
			{
				ft_putstr_fd("var -> ", 1);
				ft_putstr_fd(env_obj->name, 1);
				ft_putstr_fd(" |", 1);
				if (env_obj->values)
					ft_putstr_fd(env_obj->values[0], 1);
				ft_putstr_fd("|\n", 1);
			}
		}
		execute_cmds(data.cmds);
		clear_cmds(data.cmds, 0);
	}

	clear_inputline(data.i_line);
	clear_cmds(data.cmds, 1);
	clear_envs(&data);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
