/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:31:32 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/31 21:52:06 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"

	// juntar todos os parametros caso existam.
void	builtin_echo(t_cmd *builtin, int fd[])
{
	char	*aux;
	int		i;

	aux = ft_strdup(builtin->parans[1]);
	if (aux)
	{
		i = 1;
		if (ft_strncmp(aux, "-n", ft_strlen("-n")) == 0)
			i = 2;
		while (builtin->parans[i])
		{
			ft_putstr_fd(builtin->parans[i], fd[1]);
			i++;
			if (builtin->parans[i])
				ft_putstr_fd(" ", fd[1]);
		}
		if (ft_strncmp(aux, "-n", ft_strlen("-n")) != 0)
			ft_putchar_fd('\n', fd[1]);
	}
	free(aux);
}
