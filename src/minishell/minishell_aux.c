/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:57:13 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/19 22:08:35 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../minishell.h>

void	treat_errors(t_data *data)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = data->cmds->first_cmd;
	while (i < data->cmds->qty)
	{
		if (temp->error == 0)
		{
			printf("command not found: %s\n", temp->bin);
			data->exit_code = 127;
		}
		i++;
		if (i < data->cmds->qty)
			temp = temp->next;
	}
}
