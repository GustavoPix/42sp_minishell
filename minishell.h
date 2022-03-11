/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:54:58 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/10 22:50:58 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include "./src/inputline/inputline.h"
#include "./src/path/path.h"
#include "./src/cmds/cmds.h"

typedef struct s_env
{
	char *name;
	char **values;
} t_env;

typedef struct s_data
{
	t_inputline *i_line;
	t_cmds *cmds;
	t_env **envs;
	int qty_env;
} t_data;

void start_envs(t_data *data, char **env);
void clear_envs(t_data *data);

#endif