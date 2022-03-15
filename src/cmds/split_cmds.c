/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:04:07 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/15 19:57:24 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static void treatment_signal(t_cmds *cmds, char **str, char c)
{
	int i_char;
	// char *str_nominnor;
	char *aux;

	i_char = has_minnor_signal(*str, c);
	if (cmds->file_in && c == '<')
		free(cmds->file_in);
	if (cmds->file_out && c == '>')
		free(cmds->file_out);
	if (c == '<')
	{
		cmds->file_in = ft_strtrim(&str[0][i_char + 1], " ");
		if (has_minnor_signal(*str, '>') > -1)
			treatment_signal(cmds, &cmds->file_in, '>');
	}
	else
	{
		cmds->file_out = ft_strtrim(&str[0][i_char + 1], " ");
		if (has_minnor_signal(*str, '<') > -1)
			treatment_signal(cmds, &cmds->file_out, '<');
	}
	if (i_char == 0)
	{
		return;
	}
	else
	{
		aux = *str;
		*str = ft_calloc(sizeof(char), i_char + 1);
		ft_strlcpy(str[0], aux, i_char + 1);

		// aux = ft_split(str_nominnor, ' ');
		free(aux);
	}
}

static void setup_cmd(t_cmds *cmds, char *str)
{
	char **aux;

	int i_minus;
	int i_major;
	int args;

	args = 0;
	i_minus = has_minnor_signal(str, '<');
	i_major = has_minnor_signal(str, '>');
	if (i_minus > -1 || i_major > -1)
	{
		if (i_minus < i_major)
		{
			if (i_minus > -1)
				treatment_signal(cmds, &str, '<');
			else
				treatment_signal(cmds, &str, '>');
		}
		else
		{
			if (i_major > -1)
				treatment_signal(cmds, &str, '>');
			else
				treatment_signal(cmds, &str, '<');
		}
		if (i_minus == 0 && i_major == 0)
		{
			return;
		}
	}
	// else
	swap_char_quote(str, ' ', 1);
	aux = ft_split(str, ' ');
	free(str);
	t_cmd *cmd;
	cmd = malloc(sizeof(t_cmd));
	cmd->bin = ft_strdup(aux[0]);
	while (aux[args])
		args++;
	cmd->parans = malloc((args + 1) * sizeof(char *));
	args = 1;
	while (aux[args])
	{
		swap_char_quote(aux[args], 1, ' ');
		remove_quote(aux[args]);
		cmd->parans[args] = ft_strdup(aux[args]);
		free(aux[args]);
		args++;
	}
	free(aux[0]);
	cmd->parans[args] = NULL;
	cmd->parans[0] = "";
	cmd->bultin = 0;
	free(aux);
	if (cmds->qty == 0)
		cmds->first_cmd = cmd;
	else
		cmds->last_cmd->next = cmd;
	cmds->last_cmd = cmd;
	cmds->qty++;
	cmd->bultin = 0;
}

void split_cmds(t_cmds *cmds, char *str)
{
	char **aux;
	int i;

	i = 0;
	aux = ft_split(str, '|');

	while (aux[i])
	{
		setup_cmd(cmds, aux[i]);
		// free(aux[i]);
		i++;
	}
	free(aux);
}
