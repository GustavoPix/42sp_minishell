/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inoutfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:50:06 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/05 22:26:08 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static int position_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char *minor_theatment(t_cmds *cmds, char *str)
{
	int i_minor;
	char *aux;

	i_minor = position_char(str, '<');
	if (i_minor >= 0)
	{
		if (cmds->file_in)
			free(cmds->file_in);
		cmds->file_in = ft_strtrim(&str[i_minor + 1], " ");
		aux = str;
		str = ft_calloc(sizeof(char), i_minor);
		ft_strlcpy(str, aux, i_minor - 1);
		free(aux);
		return (str);
	}
	return (str);
}

void minor_major_setup(t_cmds *cmds, char *str)
{
	return minor_theatment(cmds, str);
}
