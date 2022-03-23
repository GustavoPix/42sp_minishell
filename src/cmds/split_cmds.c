/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:04:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/22 22:56:02 by wjuneo-f         ###   ########.fr       */
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

static void	signal_choose_tr(t_cmds *cmds, char **str)
{
	int		i_minus;
	int		i_major;

	i_minus = has_minnor_signal(*str, '<');
	i_major = has_minnor_signal(*str, '>');
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
	if (cmds->qty == 0)
		cmds->first_cmd = cmd;
	else
		cmds->last_cmd->next = cmd;
	cmds->last_cmd = cmd;
	cmds->qty++;
	if (cmds->file_in)
		cmds->fd_file_in = open(cmds->file_in, O_WRONLY);
	if (cmds->file_out)
		cmds->fd_file_out = open(cmds->file_in, O_WRONLY);
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
		remove_quote(aux[args]);
		cmd->parans[args] = ft_strdup(aux[args]);
		free(aux[args]);
		args++;
	}
	setup_default_params(cmds, cmd, args);
	free(aux[0]);
	free(aux);
}

void	split_cmds(t_cmds *cmds, char *str)
{
	char	**aux;
	int		i;

	i = 0;
	aux = ft_split(str, '|');
	while (aux && aux[i])
	{
		setup_cmd(cmds, aux[i]);
		i++;
	}
	free(aux);
}
