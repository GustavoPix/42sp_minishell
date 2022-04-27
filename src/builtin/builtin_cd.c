/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:29:38 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/27 12:38:39 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cmds/cmds.h"
#include "../minishell.h"

void	builtin_cd(t_data *data, t_cmd *btin)
{
	int		chreturn;
	char	oldpdw[255];
	t_env	*env_oldpwd;

	chreturn = -1;
	getcwd(oldpdw, 255);
	if ((btin->parans[1] == NULL || strncmp(btin->parans[1], "~", 1) == 0))
		chreturn = chdir(getenv("HOME"));
	else if (strncmp(btin->parans[1], "-", 1) == 0)
	{
		env_oldpwd = get_env(data, "OLDPWD");
		if (env_oldpwd)
			chreturn = chdir(env_oldpwd->values[0]);
		else
			printf("minishell: cd: OLDPWD not set\n");
	}
	else if (strncmp(btin->parans[1], "..", 2) == 0)
		chreturn = chdir("..");
	else if (strncmp(btin->parans[1], ".", 1) == 0)
		chreturn = chdir(".");
	else
		chreturn = chdir(btin->parans[1]);
	if (chreturn == -1)
		fprintf(stderr, "cd: %s: No such file or directory\n", btin->parans[1]);
	else
		set_env_value(data, "OLDPWD", oldpdw);
}
