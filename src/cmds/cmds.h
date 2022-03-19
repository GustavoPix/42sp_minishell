/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:18:34 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/19 16:51:24 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "../inputline/inputline.h"
# include "../../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int		bultin;
	char	*bin;
	char	**parans;
	void	*next;
	int		document;
} t_cmd;

typedef struct s_cmds
{
	int		qty;
	char	*file_in;
	char	*file_out;
	t_cmd	*first_cmd;
	t_cmd	*last_cmd;
}			t_cmds;

t_cmds	*start_cmds(void);
void	split_cmds(t_cmds *cmds, char *str);
void	clear_cmds(t_cmds *cmds, int all);
void	split_minnor_char(t_cmds *cmds);
int		has_minnor_signal(char *str, char c);
void	swap_char_quote(char *str, int from, int to);
void	remove_quote(char *str);
int		count_size_matrix(char **str);

void	debug_cmds(t_cmds *cmds);

// My alteration
int		execute_cmds(t_data *data, t_cmds *cmds);
void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[]);
// finish

void	builtin_cd(t_cmd *builtin, int fd[]);
void	builtin_echo(t_cmd *builtin, int fd[]);
void	builtin_env(t_cmd *builtin, int fd[], char *envp[]);
void	builtin_export(t_cmd *builtin, int fd[], char *envp[]);
void	builtin_pwd(t_cmd *builtin, int fd[]);
void	builtin_unset(t_cmd *builtin, int fd[], char *envp[]);

#endif
