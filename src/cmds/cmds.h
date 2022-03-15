/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:18:34 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/15 18:52:06 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
#define CMDS_H

#include "../inputline/inputline.h"
#include "../../libft/libft.h"

typedef struct s_cmd
{
	int bultin;
	char *bin;
	char **parans;
	void *next;
} t_cmd;

typedef struct s_cmds
{
	int qty;
	char *file_in;
	char *file_out;
	t_cmd *first_cmd;
	t_cmd *last_cmd;
} t_cmds;

t_cmds *start_cmds();
void split_cmds(t_cmds *cmds, char *str);
void clear_cmds(t_cmds *cmds, int all);
void split_minnor_char(t_cmds *cmds);
int has_minnor_signal(char *str, char c);
void swap_char_quote(char *str, int from, int to);
void remove_quote(char *str);

void debug_cmds(t_cmds *cmds);

#endif
