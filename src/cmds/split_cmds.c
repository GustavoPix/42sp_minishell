/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:04:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 21:00:24 by glima-de         ###   ########.fr       */
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
	cmd->error_fopen = 0;
	if (cmds->qty == 0)
		cmds->first_cmd = cmd;
	else
		cmds->last_cmd->next = cmd;
	cmds->last_cmd = cmd;
	cmds->qty++;
	// if (cmds->file_in)
	// 	cmds->fd_file_in = open(cmds->file_in, O_RDONLY, 0666);
	cmd->file_in = 0;
	cmd->file_out = 0;
	cmd->fd_file_out = 0;
	cmd->fd_file_in = 0;
	cmd->append_outfile = 0;
	cmd->error = 0;
}

static void	move_parans(t_cmd *cmd, int index, int qty)
{
	while (cmd->parans[index + qty])
	{
		cmd->parans[index] = cmd->parans[index + qty];
		cmd->parans[index + qty] = NULL;
		index++;
	}
}

static char	*signal_treatment(t_cmd *cmd, int i, int pos, int size)
{
	char	*aux;

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

static void reduce_samevar(char **str, char c)
{
	char *aux;
	int pos;

	pos = has_minnor_signal(str[0], c);
	if (pos >= 0)
	{
		aux = str[0];
		str[0] = ft_strdup(&aux[pos + 1]);
		free(aux);
		reduce_samevar(str, c);
	}
}

static void reduce_parans(char **str_ori, char **str_dest, char c, int size)
{
	char *aux;
	char *aux_dst;
	int pos;

	if (!str_ori || !str_ori[0])
		return ;
	if (size == 1)
		pos = has_minnor_signal(str_ori[0], c);
	else
		pos = has_double_signal(str_ori[0], c);
	if (pos >= 0)
	{
		aux = str_ori[0];
		str_ori[0] = ft_calloc(sizeof(char), pos + size);
		ft_strlcpy(str_ori[0], aux, pos + 1);
		aux_dst = ft_strdup(&aux[pos + 1]);
		free(aux);
		free(str_dest[0]);
		str_dest[0] = aux_dst;
		reduce_samevar(str_dest, c);
	}
}

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
			pos = has_minnor_signal(cmd->parans[i], '>');
			if (pos >= 0)
			{
				if (cmd->file_out)
					free(cmd->file_out);
				cmd->file_out = signal_treatment(cmd, i, pos, 1);
				cmd->append_outfile = 0;
				continue ;
			}
		}
		i++;
	}
	if (cmd->file_out)
		reduce_samevar(&cmd->file_out, '>');
}

static char *valid_fopen(char *path)
{
	if (access(path, R_OK))
		return (ft_strdup(path));
	return (NULL);
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
	else if (cmd->file_out)
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
