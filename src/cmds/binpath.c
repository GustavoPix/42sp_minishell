/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:34:12 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/22 21:50:22 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "../minishell.h"

static int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->bin, "echo", ft_strlen("echo")) == 0)
		cmd->bultin = 1;
	if (ft_strncmp(cmd->bin, "cd", ft_strlen("cd")) == 0)
		cmd->bultin = 1;
	if (ft_strncmp(cmd->bin, "pwd", ft_strlen("pwd")) == 0)
		cmd->bultin = 1;
	if (ft_strncmp(cmd->bin, "export", ft_strlen("export")) == 0)
		cmd->bultin = 1;
	if (ft_strncmp(cmd->bin, "unset", ft_strlen("unset")) == 0)
		cmd->bultin = 1;
	if (ft_strncmp(cmd->bin, "env", ft_strlen("env")) == 0)
		cmd->bultin = 1;
	if (ft_strncmp(cmd->bin, "exit", ft_strlen("exit")) == 0)
		cmd->bultin = 1;
	return (cmd->bultin);
}

int	test_and_apply_bin(t_data *data, t_cmd *cmd)
{
	t_env	*env_bin;
	int		i;
	char	*aux;
	char	*test_bin;

	if (is_builtin(cmd) || access(cmd->bin, F_OK) == 0)
		return (1);
	env_bin = get_env(data, "PATH");
	i = 0;
	while (env_bin->values[i])
	{
		aux = ft_strjoin(env_bin->values[i], "/");
		test_bin = ft_strjoin(aux, cmd->bin);
		free(aux);
		if (access(test_bin, F_OK) == 0)
		{
			free(cmd->bin);
			cmd->bin = test_bin;
			return (1);
		}
		free(test_bin);
		i++;
	}
	return (0);
}
