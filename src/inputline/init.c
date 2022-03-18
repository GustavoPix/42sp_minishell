/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:29:14 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/17 20:52:23 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputline.h"

t_inputline	*start_inputline(void)
{
	t_inputline	*iline;

	iline = malloc(sizeof(t_inputline));
	iline->path = calloc(255, sizeof(char));
	iline->input = calloc(1, sizeof(char));
	getcwd(iline->path, 255);
	return (iline);
}
