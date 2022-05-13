/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:18:04 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/12 21:19:11 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputline.h"

char	*get_env_name(char *str)
{
	int		i;
	int		qty;
	char	*aux;

	i = 0;
	qty = 0;
	while (ft_isalpha(str[qty]) || ft_isdigit(str[qty]))
		qty++;
	aux = ft_calloc(sizeof(char), qty + 1);
	while (i < qty)
	{
		aux[i] = str[i];
		i++;
	}
	return (aux);
}

int	index_of_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
