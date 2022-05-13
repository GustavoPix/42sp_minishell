/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:04:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 22:05:10 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static int loop_swapchar_cmd(t_cmd *cmd, char *str, int args)
{
	char	**aux;
	aux = ft_split(str, ' ');
	cmd->bin = ft_strdup(aux[0]);
	cmd->parans = malloc((count_size_matrix(aux) + 1) * sizeof(char *));
	while (aux[args])
	{
		swap_char_quote(aux[args], 1, ' ');
		swap_char_quote(aux[args], 2, '|');
		swap_char_quote(aux[args], '>', 1);
		swap_char_quote(aux[args], '<', 2);
		remove_quote(aux[args]);
		cmd->parans[args] = ft_strdup(aux[args]);
		free(aux[args]);
		args++;
	}
	free(aux[0]);
	free(aux);
	return (args);
}

static void	setup_cmd(t_cmds *cmds, char *str)
{
	int		args;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	swap_char_quote(str, ' ', 1);
	args = loop_swapchar_cmd(cmd, str, 1);
	free(str);
	cmd->file_out = 0;
	cmd->append_outfile = 0;
	setup_default_params(cmds, cmd, args);
	set_cmd_files(cmd);
}

void	split_cmds(t_cmds *cmds, char *str)
{
	char	**aux;
	int		i;

	i = 0;
	swap_char_quote(str, '|', 2);
	aux = ft_split(str, '|');
	while (aux && aux[i])
	{
		setup_cmd(cmds, aux[i]);
		i++;
	}
	free(aux);
}
