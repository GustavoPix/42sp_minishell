/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:57:03 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/03/31 21:10:59 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	start_all(t_data *data, char **env)
{
	clear();
	data->fd = 0;
	data->i_line = start_inputline();
	data->cmds = start_cmds();
	start_envs(data, env);
}

int main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	start_all(&data, env);
	loop_minishell(&data);

	//close(0);
	//close(3);
	//close(2);
	//close(1);
	//close(4);
	return (0);
}
