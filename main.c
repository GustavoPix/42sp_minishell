/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:52:47 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/07 22:09:33 by wjuneo-f         ###   ########.fr       */
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
		//debug_cmds(data.cmds);
		while (data.cmds->qty)
		{
			execute_cmds(data.cmds);
			data.cmds->qty--;
		}
		clear_cmds(data.cmds, 0);
	}
	clear_inputline(data.i_line);
	clear_cmds(data.cmds, 1);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
