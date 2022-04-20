/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:22:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/19 21:09:45 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "../minishell.h"


void    init_sigaction(struct sigaction *action, void (*handler)(int), int sig)
{
    action->sa_handler = handler;
    action->sa_flags = SA_SIGINFO;
    sigemptyset(&action->sa_mask);
    sigaction(sig, action, NULL);
}

void	handler_int(int sig)
{
	(void)sig;
	printf("\n");
 	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_int_fork(int sig)
{
	(void)sig;
	exit (0);
}
