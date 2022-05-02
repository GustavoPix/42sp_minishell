/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:57:03 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/02 20:33:08 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "src/signals/signals.h"
#include <signal.h>

static void	start_all(t_data *data, char **env)
{
	printf("\033[H\033[J");
	data->fd = 0;
	data->exit_code = 0;
	data->i_line = start_inputline();
	data->cmds = start_cmds();
	start_envs(data, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_action	action;

	(void)argc;
	(void)argv;
	data.stdin_fd = dup(0);
	start_all(&data, env);
	loop_minishell(&data, &action);
	return (0);
}
