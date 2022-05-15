/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:16:27 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/15 12:29:07 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strdup_s1(const char *s1)
{
	size_t	i;
	char	*copy_s1;

	i = 0;
	copy_s1 = ft_calloc(ft_strlen(s1) + 1, 1);
	while (s1[i] && s1[i] != '\n')
	{
		copy_s1[i] = s1[i];
		i++;
	}
	return (copy_s1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	char	*copy_s1;

	copy_s1 = strdup_s1(s1);
	i = 0;
	while ((copy_s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] && (unsigned char) !s2[i])
		{
			free(copy_s1);
			return (1);
		}
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
		{
			free(copy_s1);
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	if (copy_s1)
		free(copy_s1);
	return (0);
}
