/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:37:23 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 22:11:04 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

void	replace_char(char *str, int from, int to)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == from)
			str[i] = to;
		i++;
	}
}

void	setup_default_params(t_cmds *cmds, t_cmd *cmd, int args_count)
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
	cmd->file_in = 0;
	cmd->file_out = 0;
	cmd->fd_file_out = 0;
	cmd->fd_file_in = 0;
	cmd->append_outfile = 0;
	cmd->error = 0;
}

char	*valid_fopen(char *path)
{
	if (access(path, R_OK))
		return (ft_strdup(path));
	return (NULL);
}
