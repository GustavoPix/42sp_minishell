/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:29:38 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/20 14:31:22 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"

// sempre que atualizarmos o cd atual, também atualizar o OLDPWD.
void	builtin_cd(t_cmd *btin, int fd[])
{
	int		chreturn;

	(void)fd;
	if ((btin->parans[1] == NULL || strncmp(btin->parans[1], "~", 1) == 0))
		chreturn = chdir(getenv("HOME"));
	else if (strncmp(btin->parans[1], "-", 1) == 0)
		chreturn = chdir(getenv("OLDPWD"));
	else if (strncmp(btin->parans[1], ".", 1) == 0)
		chreturn = chdir(".");
	else if (strncmp(btin->parans[1], "..", 2) == 0)
		chreturn = chdir("..");
	else
		chreturn = chdir(btin->parans[1]);
	if (chreturn == -1)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", btin->parans[1]);
	}
}
