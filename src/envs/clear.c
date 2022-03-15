/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:54:38 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/10 23:51:12 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clear_envs(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->qty_env)
	{
		j = 0;
		if (data->envs[i]->name)
			free(data->envs[i]->name);
		while (data->envs[i]->values && data->envs[i]->values[j])
		{
			free(data->envs[i]->values[j]);
			j++;
		}
		free(data->envs[i]->values);
		free(data->envs[i]);
		i++;
	}
	free(data->envs);
}
