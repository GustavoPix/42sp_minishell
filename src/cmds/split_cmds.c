/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:04:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/05 21:14:46 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static void	treatment_signal(t_cmds *cmds, char **str, char c)
{
	int		i_char;
	char	*aux;

	i_char = has_minnor_signal(*str, c);
	if (c == '<')
	{
		free(cmds->file_in);
		cmds->file_in = ft_strtrim(&str[0][i_char + 1], " ");
		if (has_minnor_signal(*str, '>') > -1)
			treatment_signal(cmds, &cmds->file_in, '>');
	}
	else
	{
		free(cmds->file_out);
		cmds->file_out = ft_strtrim(&str[0][i_char + 1], " ");
		if (has_minnor_signal(*str, '<') > -1)
			treatment_signal(cmds, &cmds->file_out, '<');
	}
	if (i_char != 0)
	{
		aux = *str;
		*str = ft_calloc(sizeof(char), i_char + 1);
		ft_strlcpy(str[0], aux, i_char + 1);
		free(aux);
	}
}

static int detect_outfile(t_cmds *cmds, char **str)
{
	int i_major;

	i_major = has_double_signal(*str, '>');
	if (i_major >= 0)
	{
		cmds->append_outfile = 1;
		ft_memmove(&str[0][i_major], &str[0][i_major + 1], ft_strlen(&str[0][i_major + 1]));
		str[0][ft_strlen(*str) - 1] = '\0';
	}
	else
		i_major = has_minnor_signal(*str, '>');
	return (i_major);
}

static void	signal_choose_tr(t_cmds *cmds, char **str)
{
	int		i_minus;
	int		i_major;

	i_minus = has_minnor_signal(*str, '<');
	i_major = detect_outfile(cmds, str);
	if (i_minus > -1 || i_major > -1)
	{
		if (i_minus < i_major)
		{
			if (i_minus > -1)
				treatment_signal(cmds, str, '<');
			else
				treatment_signal(cmds, str, '>');
		}
		else
		{
			if (i_major > -1)
				treatment_signal(cmds, str, '>');
			else
				treatment_signal(cmds, str, '<');
		}
		if (i_minus == 0 && i_major == 0)
			return ;
	}
}

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
		cmds->fd_file_in = open(cmds->file_in, O_RDONLY, 0777);
	if (cmds->file_out)
		cmds->fd_file_out = open(cmds->file_out, O_RDWR | O_CREAT, 0777);
}

static void hero_doc(t_cmd *cmd)
{
	int i;
	int pos;
	char *aux;

	i = 0;
	while (cmd->parans[i])
	{
		pos = has_double_signal(cmd->parans[i], '<');
		if (pos >= 0)
		{
			aux = ft_strtrim(&cmd->parans[i][pos + 2], " ");
			if (ft_strlen(aux))
			{
				cmd->doc_end = aux;
				ft_bzero(cmd->parans[i], ft_strlen(cmd->parans[i]));
				cmd->parans[i] = NULL;
			}
			else
			{
				cmd->doc_end = ft_strdup(cmd->parans[i + 1]);
				ft_bzero(cmd->parans[i], ft_strlen(cmd->parans[i]));
				ft_bzero(cmd->parans[i + 1], ft_strlen(cmd->parans[i + 1]));
				cmd->parans[i] = NULL;
				cmd->parans[i + 1] = NULL;
				free(aux);
			}
			cmd->document = 1;
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
	signal_choose_tr(cmds, &str);
	swap_char_quote(str, ' ', 1);
	aux = ft_split(str, ' ');
	free(str);
	cmd->bin = ft_strdup(aux[0]);
	cmd->parans = malloc((count_size_matrix(aux) + 1) * sizeof(char *));
	args = 1;
	while (aux[args])
	{
		swap_char_quote(aux[args], 1, ' ');
		swap_char_quote(aux[args], 2, '|');
		remove_quote(aux[args]);
		cmd->parans[args] = ft_strdup(aux[args]);
		free(aux[args]);
		args++;
	}
	setup_default_params(cmds, cmd, args);
	hero_doc(cmd);
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
