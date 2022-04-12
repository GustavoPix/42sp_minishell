/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:22:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/12 20:40:37 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "../minishell.h"


void	determine_sigs(int sig)
{
	if (sig == SIGINT)
	{
		
	}
}
void	*treat_sigs(int sig, siginfo_t *sitinfo, void *wtf)
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
