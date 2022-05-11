/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:29:14 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/11 03:49:25 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputline.h"

t_inputline	*start_inputline(void)
{
	t_inputline	*iline;

	iline = malloc(sizeof(t_inputline));
	iline->path = ft_calloc(255, sizeof(char));
	iline->input = ft_calloc(1, sizeof(char));
	getcwd(iline->path, 255);
	return (iline);
}
