/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inoutfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:50:06 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/28 19:28:52 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

int	has_minnor_signal(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i + 1] && str[i + 1] == c)
			{
				i += 2;
				continue;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int	has_double_signal(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i + 1] && str[i + 1] == c)
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}
