/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:54:35 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/17 20:49:20 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clear_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	start_envs(t_data *data, char **env)
{
	int		i;
	int		j;
	t_env	**envs;
	char	**aux;

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
		clear_matrix(aux);
		i++;
	}
	data->envs = envs;
}
