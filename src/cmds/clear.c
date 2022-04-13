/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:01:35 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/12 20:43:45 by glima-de         ###   ########.fr       */
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
	if (cmd->doc_end)
		free(cmd->doc_end);
	if (cmd->file_out)
	{
		close(cmd->fd_file_out);
		free(cmd->file_out);
		cmd->file_out = 0;
	}
	cmd->append_outfile = 0;
	cmd->document = 0;
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
		close(cmds->fd_file_in);
		cmds->fd_file_in = 0;
	}
	if (cmds->file_out)
	{
		free(cmds->file_out);
		cmds->file_out = 0;
		close(cmds->fd_file_out);
		cmds->fd_file_out = 0;
		cmds->append_outfile = 0;
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
