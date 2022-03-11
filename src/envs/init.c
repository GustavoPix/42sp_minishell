/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:54:35 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/11 00:00:35 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void start_envs(t_data *data, char **env)
{
	int i;
	int j;
	t_env **envs;
	char **aux;

	i = 0;
	while (env[i])
		i++;
	envs = malloc(sizeof(t_env *) * i);
	data->qty_env = i;
	i = 0;
	while (env[i])
	{
		envs[i] = malloc(sizeof(t_env));
		aux = ft_split(env[i], '=');
		envs[i]->name = ft_strdup(aux[0]);
		if (aux[1] && ft_strlen(aux[1]))
			envs[i]->values = ft_split(aux[1], ':');
		else
			envs[i]->values = 0;
		j = 0;
		while (aux[j])
		{
			free(aux[j]);
			j++;
		}
		free(aux);
		i++;
	}

	i = 0;
	while (i < data->qty_env)
	{
		ft_putstr_fd(envs[i]->name, 1);
		ft_putchar_fd('\n', 1);

		int j = 0;
		while (envs[i]->values && envs[i]->values[j])
		{
			ft_putstr_fd(envs[i]->values[j], 1);
			ft_putstr_fd("  -  ", 1);
			j++;
		}
		ft_putstr_fd("\n\n", 1);
		i++;
	}
	data->envs = envs;
}
