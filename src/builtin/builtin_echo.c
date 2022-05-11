/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:31:32 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/11 03:55:03 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"

// juntar todos os parametros caso existam.
void	builtin_echo(t_cmd *builtin, int fd[])
{
	char	*aux;
	int		i;
	int		pn;

	(void)fd;
	pn = 0;
	aux = NULL;
	if (builtin->parans[1])
		aux = ft_strdup(builtin->parans[1]);
	if (aux)
	{
		i = 1;
		if (ft_strncmp(aux, "-n", ft_strlen("-n")) == 0)
			i = 2;
		while (builtin->parans[i])
		{
			if (ft_strncmp(builtin->parans[i], "-n", 2) || pn)
			{
				ft_putstr_fd(builtin->parans[i], STDOUT_FILENO);
				i++;
				if (builtin->parans[i])
					ft_putstr_fd(" ", STDOUT_FILENO);
			}
			else
			{
				pn = 1;
				i++;
			}
		}
		if (ft_strncmp(aux, "-n", ft_strlen("-n")) != 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		free(aux);
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
}
