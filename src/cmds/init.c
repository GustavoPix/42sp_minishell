/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:22:16 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/28 21:50:44 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

t_cmds	*start_cmds(void)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	cmds->qty = 0;
	cmds->file_in = 0;
	cmds->file_out = 0;
	return (cmds);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("----\n", 1);
	ft_putstr_fd(cmd->bin, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("document -> |", 1);
	if (cmd->document)
		ft_putstr_fd(cmd->doc_end, 1);
	ft_putstr_fd("|\n", 1);

	while (cmd->parans[i])
	{
		ft_putstr_fd(cmd->parans[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_putstr_fd("----\n", 1);
}

void	debug_cmds(t_cmds *cmds)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = cmds->first_cmd;
	ft_putstr_fd("file in -> |", 1);
	if (cmds->file_in)
		ft_putstr_fd(cmds->file_in, 1);
	ft_putstr_fd("|\n", 1);
	ft_putstr_fd("file out -> |", 1);
	if (cmds->file_out)
		ft_putstr_fd(cmds->file_out, 1);
	ft_putstr_fd("|\n", 1);
	while (i < cmds->qty)
	{
		print_cmd(cmd);
		i++;
		if (i < cmds->qty)
			cmd = cmd->next;
	}
}
