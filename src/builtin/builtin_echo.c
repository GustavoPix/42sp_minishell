/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:31:32 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/20 14:31:55 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"

	// juntar todos os parametros caso existam.
void	builtin_echo(t_cmd *builtin, int fd[])
{
	(void)fd;
	if (builtin->parans[1])
	{
		if (ft_strncmp(builtin->parans[1], "-n", ft_strlen("-n")) == 0)
		{
			write(1, builtin->parans[2], ft_strlen(builtin->parans[2] - 1));
		}
		else
		{
			ft_putstr_fd(builtin->parans[1], 1);
		}
	}
	ft_putchar_fd('\n', 1);
}
