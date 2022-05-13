/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:22:16 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 21:33:14 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "../minishell.h"

void	setup_cmds_bin_path(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmds->first_cmd;
	while (i < data->cmds->qty)
	{
		cmd->error = test_and_apply_bin(data, cmd);
		i++;
		if (i < data->cmds->qty)
			cmd = cmd->next;
	}
}

t_cmds	*start_cmds(void)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	cmds->qty = 0;
	return (cmds);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("----\n");
	printf("%s\n", cmd->bin);
	printf("document ->  |%s|\n", cmd->doc_end);
	printf("file in ->   |%s|\n", cmd->file_in);
	printf("file out ->  |%s|\n", cmd->file_out);
	printf("Append file: ");
	if (cmd->append_outfile)
		printf("Yes\n");
	else
		printf("No\n");
	printf("cmd error:   |%i|\n", cmd->error);
	while (cmd->parans[i])
	{
		printf("%s\n", cmd->parans[i]);
		i++;
	}
	printf("----\n");
}

void	debug_cmds(t_cmds *cmds)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = cmds->first_cmd;
	printf("Append file: ");
	while (i < cmds->qty)
	{
		print_cmd(cmd);
		i++;
		if (i < cmds->qty)
			cmd = cmd->next;
	}
}
