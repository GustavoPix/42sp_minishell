/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:57:03 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/03/31 20:32:44 by wjuneo-f         ###   ########.fr       */
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
