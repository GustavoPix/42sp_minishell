/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:00:02 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/20 14:29:24 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"

// lembrar de dar join nos parans;
void	builtin_unset(t_data *data, t_cmd *builtin, int fd[])
{
	(void)fd;
	remove_env(data, builtin->parans[1]);
}
