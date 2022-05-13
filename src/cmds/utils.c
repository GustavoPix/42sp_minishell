/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:28:18 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 21:37:00 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

int	count_size_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	move_parans(t_cmd *cmd, int index, int qty)
{
	while (cmd->parans[index + qty])
	{
		cmd->parans[index] = cmd->parans[index + qty];
		cmd->parans[index + qty] = NULL;
		index++;
	}
}

char	*signal_treatment(t_cmd *cmd, int i, int pos, int size)
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

void	reduce_samevar(char **str, char c)
{
	char	*aux;
	int		pos;

	pos = has_minnor_signal(str[0], c);
	if (pos >= 0)
	{
		aux = str[0];
		str[0] = ft_strdup(&aux[pos + 1]);
		free(aux);
		reduce_samevar(str, c);
	}
}

void	reduce_parans(char **str_ori, char **str_dest, char c, int size)
{
	char	*aux;
	char	*aux_dst;
	int		pos;

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
