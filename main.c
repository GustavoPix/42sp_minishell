/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:57:03 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/04/13 16:10:44 by wjuneo-f         ###   ########.fr       */
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
	t_data				data;
	// struct sigaction	action_int;
	// struct sigaction	action_quit;
	struct sigaction	action;


	action.sigaction = treat_sigs;
	action.sa_flags = SA_SIGINFO;
	init_sigaction(&action, SIG_IGN, SIGQUIT);
	// action_quit.sa_handler = treat_sigs;
	// action_quit.sa_flags = SA_SIGINFO;
	// action_quit.sa_mask = SIG_IGN;
	data.stdin_fd = dup(0);
	// sigaction(SIGINT, &action_int, NULL);
	// sigaction(SIGQUIT, &action_quit, NULL);
	start_all(&data, env);
	loop_minishell(&data);
	(void)argc;
	(void)argv;
	return (0);
}
