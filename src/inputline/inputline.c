/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:25:23 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/13 20:23:17 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputline.h"
#include "../minishell.h"

static char *get_env_name(char *str)
{
	int i;
	int qty;
	char *aux;

	i = 0;
	qty = 0;
	while (str[qty] && str[qty] != ' ')
		qty++;
	aux = ft_calloc(sizeof(char), qty + 1);
	while (i < qty)
	{
		aux[i] = str[i];
		i++;
	}
	return (aux);
}

static int index_of_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int replace_local_vars(t_data *data)
{
	int dollarPos;
	char *var_name;
	t_env *env;
	char *aux;
	char *value_env;

	dollarPos = index_of_char(data->i_line->input, '$');
	if (dollarPos > -1)
	{
		var_name = get_env_name(&data->i_line->input[dollarPos + 1]);
		env = get_env(data, var_name);
		if (env && env->values)
			value_env = get_value_env_join(env);
		else
			value_env = ft_strdup("");
		aux = ft_calloc(sizeof(char), ft_strlen(data->i_line->input) - ft_strlen(var_name) + ft_strlen(value_env) + 1);
		int i = 0;
		int j = 0;
		while (i < dollarPos)
		{
			aux[i] = data->i_line->input[i];
			i++;
		}
		while (value_env[j])
		{
			aux[i + j] = value_env[j];
			j++;
		}
		i++;
		while (data->i_line->input[i + ft_strlen(var_name)])
		{
			aux[i + j - 1] = data->i_line->input[i + ft_strlen(var_name)];
			i++;
		}
		free(data->i_line->input);
		data->i_line->input = aux;
		free(value_env);
		free(var_name);
		return (replace_local_vars(data));
	}
	return (0);
}

void input_line(t_data *data)
{
	char *aux;
	char *to_print;

	free(data->i_line->input);
	to_print = ft_strjoin(data->i_line->path, "$ ");
	data->i_line->input = readline(to_print);
	free(to_print);
	aux = ft_strtrim(data->i_line->input, " ");
	if (aux)
	{
		add_history(aux);
		free(data->i_line->input);
		data->i_line->input = aux;
		replace_local_vars(data);
	}
}
