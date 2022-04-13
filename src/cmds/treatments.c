/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:48:11 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/12 22:46:15 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static int pos_char(char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return(i);
}


static int rev_pos_char(char *str, int c)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return(i);
}

void	swap_char_simpquote(char *str, int from, int to)
{
	int	i;
	int	in_quot;
	int quot;

	i = 0;
	in_quot = 0;
	quot = '\'';
	if (rev_pos_char(str, quot) <= pos_char(str, quot))
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == from && in_quot)
			str[i] = to;
		else if (str[i] == quot)
			in_quot = !in_quot;
		i++;
	}
}

void	swap_char_quote(char *str, int from, int to)
{
	int	i;
	int	in_quot;
	int quot;

	i = 0;
	in_quot = 0;
	if (pos_char(str, '\'') < pos_char(str, '"'))
		quot = '\'';
	else
		quot = '"';
	if (rev_pos_char(str, quot) <= pos_char(str, quot))
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == from && in_quot)
			str[i] = to;
		else if (str[i] == quot)
			in_quot = !in_quot;
		i++;
	}
}
void	replace_char(char *str, int from, int to)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == from)
			str[i] = to;
		i++;
	}
}

void	remove_quote(char *str)
{
	int quot;
	int start;
	int end;

	if (pos_char(str, '\'') < pos_char(str, '"'))
		quot = '\'';
	else
		quot = '"';
	if (rev_pos_char(str, quot) <= pos_char(str, quot))
		return ;
	start = pos_char(str, quot);
	end = rev_pos_char(str, quot);
	memmove(&str[start], &str[start + 1], end - start);
	ft_bzero(&str[end - 1], ft_strlen(str) - end);

}
