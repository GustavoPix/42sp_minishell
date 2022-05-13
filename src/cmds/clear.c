/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:01:35 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 21:32:25 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static void	clear_cmd_file(t_cmd *cmd)
{
	if (cmd->doc_end)
		free(cmd->doc_end);
	if (cmd->file_in)
	{
		close(cmd->fd_file_in);
		free(cmd->file_in);
		cmd->file_in = 0;
	}
	if (cmd->file_out)
	{
		close(cmd->fd_file_out);
		free(cmd->file_out);
		cmd->file_out = 0;
	}
}

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
	clear_cmd_file(cmd);
	if (cmd->error_fopen)
		free(cmd->error_fopen);
	cmd->append_outfile = 0;
	cmd->document = 0;
	free(cmd);
}

static void	clear_cmds_base(t_cmds *cmds, int all)
{
	cmds->qty = 0;
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
