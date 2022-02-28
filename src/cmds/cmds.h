/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:18:34 by glima-de          #+#    #+#             */
/*   Updated: 2022/02/28 15:26:58 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
#define CMDS_H

#include "../inputline/inputline.h"
#include "../../libft/libft.h"

typedef struct s_cmd
{
	char *file_in;
	char *file_out;
	int bultin;
	char *bin;
	char **parans;
	void *next;
} t_cmd;

typedef struct s_cmds
{
	int qty;
	t_cmd *first_cmd;
	t_cmd *last_cmd;
} t_cmds;

t_cmds *start_cmds();
void split_cmds(t_cmds *cmds, char *str);
void clear_cmds(t_cmds *cmds, int all);

void debug_cmds(t_cmds *cmds);

#endif
