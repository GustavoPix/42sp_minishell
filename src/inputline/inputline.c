/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:25:23 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/23 04:19:42 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputline.h"
#include "../minishell.h"

static char	*get_env_name(char *str)
{
	int		i;
	int		qty;
	char	*aux;

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

static int	index_of_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*join_between(char *sori, char *sbet, int i_split, int ssplit)
{
	char	*aux;
	int		size_new_str;

	size_new_str = ft_strlen(sori) - ssplit;
	size_new_str += ft_strlen(sbet) + 1;
	aux = ft_calloc(sizeof(char), size_new_str);
	ft_strlcpy(aux, sori, i_split + 1);
	ft_strlcpy(&aux[i_split], sbet, ft_strlen(sbet) + 1);
	i_split++;
	ft_strlcpy(
		&aux[i_split + ft_strlen(sbet) - 1],
		&sori[i_split + ssplit],
		ft_strlen(&sori[i_split + ssplit]) + 1);
	return (aux);
}

static int	replace_local_vars(t_data *data)
{
	int		dpos;
	t_env	*env;
	char	*vname;
	char	*venv;
	char	*aux;

	dpos = index_of_char(data->i_line->input, '$');
	if (dpos > -1)
	{
		vname = get_env_name(&data->i_line->input[dpos + 1]);
		env = get_env(data, vname);
		if (env && env->values)
			venv = get_value_env_join(env);
		else
			venv = ft_strdup("");
		aux = join_between(data->i_line->input, venv, dpos, ft_strlen(vname));
		free(data->i_line->input);
		data->i_line->input = aux;
		free(venv);
		free(vname);
		return (replace_local_vars(data));
	}
	return (0);
}

void	input_line(t_data *data)
{
	char	*aux;
	char	*user;

	free(data->i_line->input);
	user = getenv("USER");
	user = getenv("USER");
	printf("\033[1;34m%s\033[0;0m in", user);
	printf("\033[1;32m%s\033[0;0m\n", data->i_line->path);
	data->i_line->input = readline("✦\033[1;31m 》\033[0;0m ");
	if (!data->i_line->input)
	{
		ft_putstr_fd("exit\n", 1);
		data->i_line->input = ft_strdup("exit");
	}
	aux = ft_strtrim(data->i_line->input, " ");
	if (ft_strlen(aux))
		add_history(aux);
	free(data->i_line->input);
	data->i_line->input = aux;
	replace_local_vars(data);
}
