/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:25:23 by glima-de          #+#    #+#             */
/*   Updated: 2022/02/27 13:53:09 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputline.h"

void input_line(t_inputline *iline)
{
	char *aux;
	free(iline->input);
	iline->input = readline("$ ");
	aux = ft_strtrim(iline->input, " ");
	if (aux)
	{
		add_history(aux);
		free(iline->input);
		iline->input = aux;
	}
}
