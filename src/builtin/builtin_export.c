/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:02:21 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/22 21:05:34 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"
// lembrar de dar join nos parans;

void	builtin_export(t_data *data, t_cmd *builtin, int fd[])
{
	(void)fd;
	add_env(data, builtin->parans[1]);
}
