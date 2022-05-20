/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:33:51 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/19 21:05:59 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"

void	builtin_exit(t_data *data, t_cmd *builtin)
{
	if (data->cmds->qty == 1)
	{
		if (builtin->parans[1])
			data->exit_code_exit = ft_atoi(builtin->parans[1]);
		else
			data->exit_code_exit = 0;
		data->exit = 1;
	}
}
