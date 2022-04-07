/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:00:02 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/05 21:49:55 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"

// lembrar de dar join nos parans;
void	builtin_unset(t_data *data, t_cmd *builtin)
{
	remove_env(data, builtin->parans[1]);
}
