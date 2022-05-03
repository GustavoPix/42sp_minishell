/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:16:27 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/05/02 21:08:03 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
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
	i = 0;
	while ((copy_s1[i] || s2[i]))
	{
		if ((unsigned char) copy_s1[i] && (unsigned char) !s2[i])
			return (1);
		if ((unsigned char) copy_s1[i] != (unsigned char) s2[i])
			return ((unsigned char) copy_s1[i] - (unsigned char) s2[i]);
		i++;
	}
	free(copy_s1);
	return (0);
}
