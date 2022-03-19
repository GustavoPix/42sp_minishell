/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:24:44 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/19 17:25:22 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"

void	builtin_env(t_data *data, t_cmd *builtin, int fd[])
{
	int		i;
	t_env	*env;
	char	*aux;

	i = 0;
	(void)builtin;
	(void)fd;
	while (i < data->qty_env)
	{
		env = data->envs[i];
		ft_putstr_fd(env->name, fd[1]);
		ft_putstr_fd("=", fd[1]);
		if (env->values)
		{
			aux = get_value_env_join(env);
			ft_putstr_fd(aux, fd[1]);
			free(aux);
		}
		ft_putstr_fd("\n", fd[1]);
		i++;
	}
}
