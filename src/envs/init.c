/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:54:35 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/19 18:17:16 by glima-de         ###   ########.fr       */
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

void	add_env(t_data *data, char *env_value)
{
	t_env	**new_envs;
	char	**aux;
	int		i;

	i = 0;
	new_envs = malloc(sizeof(t_env *) * (data->qty_env + 1));
	while (i < data->qty_env)
	{
		new_envs[i] = data->envs[i];
		i++;
	}
	printf("EXPORT -> |%s|\n", env_value);
	aux = ft_split(env_value, '=');
	new_envs[i] = malloc(sizeof(t_env));
	new_envs[i]->name = ft_strdup(aux[0]);
	if (aux[1] && ft_strlen(aux[1]))
		new_envs[i]->values = ft_split(aux[1], ':');
	else
		new_envs[i]->values = 0;
	free(data->envs);
	data->envs = new_envs;
	data->qty_env++;
	clear_matrix(aux);
}

void	remove_env(t_data *data, char *env_unset)
{
	t_env	**new_envs;
	int		i;
	int		pos;

	pos = 0;
	i = 0;
	while (pos < data->qty_env)
	{
		if (ft_strcmp(env_unset, data->envs[pos]->name) == 0)
			break ;
		pos++;
	}
	new_envs = malloc(sizeof(t_env *) * (data->qty_env - 1));
	while (i < data->qty_env - 1)
	{
		if (i < pos)
			new_envs[i] = data->envs[i];
		else
			new_envs[i] = data->envs[i + 1];
		i++;
	}
	free(data->envs[pos]->name);
	clear_matrix(data->envs[pos]->values);
	free(data->envs[pos]);
	free(data->envs);
	data->envs = new_envs;
	data->qty_env--;
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
