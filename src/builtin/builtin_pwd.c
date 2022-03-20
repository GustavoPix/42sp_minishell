/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:32:09 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/20 14:32:13 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"

void	builtin_pwd(t_cmd *builtin, int fd[])
{
	char	pwd[255];

	(void)fd;
	(void)builtin;
	getcwd(pwd, sizeof(pwd));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}
