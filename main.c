/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:52:47 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/10 22:51:30 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
		show_path(data.i_line);
		input_line(data.i_line);
		split_cmds(data.cmds, data.i_line->input);
		if (data.cmds->qty == 1)
			if (ft_strncmp(data.cmds->first_cmd->bin, "cd", 2) == 0)
				gofolder(data.i_line, data.cmds->first_cmd->parans[1]);
		// split_minnor_char(data.cmds);
		debug_cmds(data.cmds);
		clear_cmds(data.cmds, 0);
	}
	clear_inputline(data.i_line);
	clear_cmds(data.cmds, 1);
	clear_envs(&data);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
