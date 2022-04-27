/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:02:21 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/23 13:41:06 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"

void	builtin_export(t_data *data, t_cmd *builtin)
{
	char	**aux;
	int		i;

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
