/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputline.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:53:25 by glima-de          #+#    #+#             */
/*   Updated: 2022/02/27 14:31:28 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTLINE_H
#define INPUTLINE_H

#include "../../libft/libft.h"
#include <unistd.h>

// Readline
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_inputline
{
	char *path;
	char *input;
} t_inputline;

t_inputline *start_inputline();
void show_path(t_inputline *iline);
void input_line(t_inputline *iline);
void clear_inputline(t_inputline *iline);

#endif
