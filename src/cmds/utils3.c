/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:48:47 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 21:53:28 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static void	hero_doc(t_cmd *cmd)
{
	int	i;
	int	pos;

	i = 0;
	reduce_parans(&cmd->bin, &cmd->doc_end, '<', 2);
	while (cmd->parans[i])
	{
		pos = has_double_signal(cmd->parans[i], '<');
		if (pos >= 0)
		{
			if (cmd->doc_end)
				free(cmd->doc_end);
			cmd->doc_end = signal_treatment(cmd, i, pos, 2);
			cmd->document = 1;
			continue ;
		}
		i++;
	}
	if (cmd->doc_end)
		cmd->document = 1;
}

static void	in_file(t_cmd *cmd)
{
	int	i;
	int	pos;

	i = 0;
	reduce_parans(&cmd->bin, &cmd->file_in, '<', 1);
	while (cmd->parans[i])
	{
		pos = has_minnor_signal(cmd->parans[i], '<');
		if (pos >= 0)
		{
			if (cmd->file_in)
			{
				if (!cmd->error_fopen)
					cmd->error_fopen = valid_fopen(cmd->file_in);
				free(cmd->file_in);
			}
			cmd->file_in = signal_treatment(cmd, i, pos, 1);
			i = 0;
			continue ;
		}
		i++;
	}
	if (cmd->file_in)
		reduce_samevar(&cmd->file_in, '<');
}

static int	out_file_minsig(t_cmd *cmd, int i)
{
	int	pos;

	pos = has_minnor_signal(cmd->parans[i], '>');
	if (pos >= 0)
	{
		if (cmd->file_out)
			free(cmd->file_out);
		cmd->file_out = signal_treatment(cmd, i, pos, 1);
		cmd->append_outfile = 0;
	}
	return (pos);
}

static void	out_file(t_cmd *cmd)
{
	int	i;
	int	pos;

	i = 0;
	reduce_parans(&cmd->bin, &cmd->file_out, '>', 1);
	reduce_parans(&cmd->file_out, &cmd->file_in, '<', 1);
	while (cmd->parans[i])
	{
		pos = has_double_signal(cmd->parans[i], '>');
		if (pos >= 0)
		{
			cmd->file_out = signal_treatment(cmd, i, pos, 2);
			cmd->append_outfile = 1;
			continue ;
		}
		else
		{
			if (out_file_minsig(cmd, i) >= 0)
				continue ;
		}
		i++;
	}
	if (cmd->file_out)
		reduce_samevar(&cmd->file_out, '>');
}

void	set_cmd_files(t_cmd *cmd)
{
	int args;

	args = 0;
	hero_doc(cmd);
	out_file(cmd);
	in_file(cmd);
	while (cmd->parans[args])
	{
		replace_char(cmd->parans[args], 1, '>');
		replace_char(cmd->parans[args], 2, '<');
		args++;
	}
	if (cmd->file_in)
		cmd->fd_file_in = open(cmd->file_in, O_RDONLY, 0666);
	if (cmd->file_out && cmd->append_outfile)
		cmd->fd_file_out = open(cmd->file_out,
				O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (cmd->file_out)
		cmd->fd_file_out = open(cmd->file_out,
				O_CREAT | O_WRONLY | O_TRUNC, 0666);
}
