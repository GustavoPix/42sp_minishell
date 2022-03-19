/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:41:36 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/17 20:49:45 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value_env_join(t_env *env)
{
	int		qty;
	char	*aux;
	char	*result;

	qty = 0;
	result = ft_calloc(sizeof(char), 1);
	while (env->values && env->values[qty])
	{
		if (qty)
			aux = ft_strjoin(result, ":");
		else
			aux = ft_strjoin(result, "");
		free(result);
		result = ft_strjoin(aux, env->values[qty]);
		free(aux);
		qty++;
	}
	return (result);
}

t_env	*get_env(t_data *data, char *env)
{
	int	i;

	i = 0;
	while (i < data->qty_env)
	{
		if (ft_strncmp(data->envs[i]->name, env, ft_strlen(env)) == 0)
			return (data->envs[i]);
		i++;
	}
	return (NULL);
}
