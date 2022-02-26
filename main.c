/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:52:47 by glima-de          #+#    #+#             */
/*   Updated: 2022/02/26 16:50:43 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int main()
{
	t_data data;
	data.i_line = start_inputline();
	while (strcmp(data.i_line->input, "exit") != 0)
	{
		show_path(data.i_line);
		input_line(data.i_line);
	}
	clear_inputline(data.i_line);
	ft_putstr_fd("Bye! ;)\n", 1);
	return (0);
}
