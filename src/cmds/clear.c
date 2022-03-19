/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:01:35 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/17 19:10:28 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

void	clear_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	free(cmd->bin);
	while (cmd->parans[i])
	{
		if (cmd->parans[i])
			free(cmd->parans[i]);
		i++;
	}
	free(cmd->parans);
	free(cmd);
}

static void	clear_cmds_base(t_cmds *cmds, int all)
{
	cmds->qty = 0;
	cmds->first_cmd = 0;
	cmds->last_cmd = 0;
	if (cmds->file_in)
	{
		free(cmds->file_in);
		cmds->file_in = 0;
	}
	if (cmds->file_out)
	{
		free(cmds->file_out);
		cmds->file_out = 0;
	}
	if (all)
		free(cmds);
}

void	clear_cmds(t_cmds *cmds, int all)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*next_cmd;

	i = 0;
	cmd = cmds->first_cmd;
	while (i < cmds->qty)
	{
		if (i + 1 < cmds->qty)
			next_cmd = cmd->next;
		clear_cmd(cmd);
		if (i + 1 < cmds->qty)
			cmd = next_cmd;
		i++;
	}
	clear_cmds_base(cmds, all);
}
