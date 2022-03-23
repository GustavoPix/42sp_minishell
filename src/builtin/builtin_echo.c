/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:31:32 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/22 21:05:27 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"

	// juntar todos os parametros caso existam.
void	builtin_echo(t_cmd *builtin, int fd[])
{
	char *aux;

	aux = ft_strdup(builtin->parans[1]);
	if (aux)
	{
		if (ft_strncmp(aux, "-n", ft_strlen("-n")) == 0)
		{
			write(fd[1], builtin->parans[2], ft_strlen(builtin->parans[2] - 1));
		}
		else
		{
			ft_putstr_fd(aux, fd[1]);
		}
	}
	ft_putchar_fd('\n', fd[1]);
	free(aux);
}
