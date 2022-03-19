/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:02:21 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/19 16:45:38 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"
// lembrar de dar join nos parans;

void	builtin_export(t_data *data, t_cmd *builtin, int fd[])
{
	//int		size_env;
	//char	*variable_export;

	(void)fd;
	//size_env = 0;
	add_env(data, builtin->parans[1]);
	//while(envp[size_env])
	//	size_env++;
	//variable_export = ft_strchr(builtin->parans[1], '=');
	//variable_export++;
	//envp[size_env] = variable_export;
	//envp++[size_env] = NULL;
}
