/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gofolder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:10:41 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/18 19:25:10 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

int	gofolder(t_inputline *iline, char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (-1);
	}
	getcwd(iline->path, 255);
	return (0);
}
