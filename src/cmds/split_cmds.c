/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:04:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/22 16:23:15 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static void	setup_default_params(t_cmds *cmds, t_cmd *cmd, int args_count)
{
	cmd->parans[args_count] = NULL;
	cmd->parans[0] = "";
	cmd->bultin = 0;
	cmd->document = 0;
	cmd->doc_end = 0;
	if (cmds->qty == 0)
		cmds->first_cmd = cmd;
	else
		cmds->last_cmd->next = cmd;
	cmds->last_cmd = cmd;
	cmds->qty++;
	if (cmds->file_in)
		cmds->fd_file_in = open(cmds->file_in, O_RDONLY, 0666);
	cmd->file_in = 0;
	cmd->file_out = 0;
	cmd->fd_file_out = 0;
}

static void move_parans(t_cmd *cmd, int index, int qty)
{
	while (cmd->parans[index + qty])
	{
		cmd->parans[index] = cmd->parans[index + qty];
		cmd->parans[index + qty] = NULL;
		index++;
	}
}

static char *signal_treatment(t_cmd *cmd, int i, int pos, int size)
{
	char *aux;

	aux = ft_strtrim(&cmd->parans[i][pos + size], " ");
	if (ft_strlen(aux))
	{
		ft_bzero(cmd->parans[i], ft_strlen(cmd->parans[i]));
		free(cmd->parans[i]);
		cmd->parans[i] = NULL;
		move_parans(cmd, i, 1);
	}
	else
	{
		free(aux);
		aux = ft_strdup(cmd->parans[i + 1]);
		ft_bzero(cmd->parans[i], ft_strlen(cmd->parans[i]));
		ft_bzero(cmd->parans[i + 1], ft_strlen(cmd->parans[i + 1]));
		free(cmd->parans[i]);
		free(cmd->parans[i + 1]);
		cmd->parans[i] = NULL;
		cmd->parans[i + 1] = NULL;
		move_parans(cmd, i, 2);
	}
	return (aux);
}

static void hero_doc(t_cmd *cmd)
{
	int i;
	int pos;

	i = 0;
	while (cmd->parans[i])
	{
		pos = has_double_signal(cmd->parans[i], '<');
		if (pos >= 0)
		{
			cmd->doc_end = signal_treatment(cmd, i, pos, 2);
			cmd->document = 1;
			continue;
		}
		i++;
	}
}

static void out_file(t_cmd *cmd)
{
	int i;
	int pos;

	i = 0;
	while (cmd->parans[i])
	{
		pos = has_double_signal(cmd->parans[i], '>');
		if (pos >= 0)
		{
			cmd->file_out = signal_treatment(cmd, i, pos, 2);
			cmd->append_outfile = 1;
			continue;
		}
		else
		{
			pos = has_minnor_signal(cmd->parans[i], '>');
			if (pos >= 0)
			{
				cmd->file_out = signal_treatment(cmd, i, pos, 1);
				cmd->append_outfile = 0;
				continue;
			}
		}
		i++;
	}
}

static void in_file(t_cmd *cmd)
{
	int i;
	int pos;

	i = 0;
	while (cmd->parans[i])
	{
		pos = has_minnor_signal(cmd->parans[i], '<');
		if (pos >= 0)
		{
			cmd->file_in = signal_treatment(cmd, i, pos, 1);
			continue;
		}
		i++;
	}
}

static void	setup_cmd(t_cmds *cmds, char *str)
{
	char	**aux;
	int		args;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	//signal_choose_tr(cmds, &str);
	swap_char_quote(str, ' ', 1);
	aux = ft_split(str, ' ');
	free(str);
	cmd->bin = ft_strdup(aux[0]);
	cmd->parans = malloc((count_size_matrix(aux) + 1) * sizeof(char *));
	args = 1;
	cmd->file_out = 0;
	cmd->append_outfile = 0;
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
	setup_default_params(cmds, cmd, args);
	hero_doc(cmd);
	out_file(cmd);
	in_file(cmd);
	args = 0;
	while (cmd->parans[args])
	{
		replace_char(cmd->parans[args], 1, '>');
		replace_char(cmd->parans[args], 2, '<');
		//printf("$%s$\n", cmd->parans[args]);
		args++;
	}
	if (cmd->file_in)
		cmd->fd_file_in = open(cmd->file_in, O_RDONLY, 0666);
	if (cmd->file_out && cmd->append_outfile)
		cmd->fd_file_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if(cmd->file_out)
		cmd->fd_file_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_TRUNC , 0666);
	free(aux[0]);
	free(aux);
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
