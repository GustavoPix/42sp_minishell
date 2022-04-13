/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:02:21 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/12 22:34:57 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"
// lembrar de dar join nos parans;

void	builtin_export(t_data *data, t_cmd *builtin)
{
	char **aux;
	int i;

	i = 0;
	if (builtin->parans[1])
	{
		aux = ft_split(builtin->parans[1], '=');
		set_env_value(data, aux[0], aux[1]);
		while (aux[i])
		{
			free(aux[i]);
			i++;
		}
		free(aux);
	}
}
