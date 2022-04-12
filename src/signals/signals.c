/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:22:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/11 22:07:30 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "../minishell.h"

void *treat_sigs(int sig, siginfo_t *sitinfo, void *wtf)
{
	(void)wtf;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		if (sitinfo->si_uid == 0)
			return (0);
		else if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	return (0);
}
