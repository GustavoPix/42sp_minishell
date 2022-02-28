/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:52:47 by glima-de          #+#    #+#             */
/*   Updated: 2022/02/28 15:27:23 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int main()
{
	t_data data;
	data.i_line = start_inputline();
	data.cmds = start_cmds();
	while (strcmp(data.i_line->input, "exit") != 0)
	{
		show_path(data.i_line);
		input_line(data.i_line);
		split_cmds(data.cmds, data.i_line->input);
		debug_cmds(data.cmds);
		clear_cmds(data.cmds, 0);
	}
	clear_inputline(data.i_line);
	clear_cmds(data.cmds, 1);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
