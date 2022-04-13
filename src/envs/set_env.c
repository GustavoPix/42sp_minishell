/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:52:27 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/07 20:29:12 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *mount_key_value(char *key, char *value)
{
	char *aux1;
	char *aux2;

	aux1 = ft_strjoin(key, "=");
	aux2 = ft_strjoin(aux1, value);
	free(aux1);
	return (aux2);
}

int	set_env_value(t_data *data, char *key, char *value)
{
	t_env *env;
	char *new;
	int i;
	char **aux;

	env = get_env(data, key);
	if (env)
	{
		i = 0;
		aux = env->values;
		while (aux[i])
		{
			free(aux[i]);
			i++;
		}
		free(aux);
		env->values = ft_split(value, ':');
	}
	else
	{
		new = mount_key_value(key, value);
		add_env(data, new);
		free(new);
	}
	return (0);
}
