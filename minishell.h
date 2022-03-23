/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:54:58 by glima-de          #+#    #+#             */
/*   Updated: 2022/03/22 21:58:14 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./src/inputline/inputline.h"
# include "./src/path/path.h"
# include "./src/cmds/cmds.h"

#define clear() printf("\033[H\033[J");

typedef struct s_env
{
	char	*name;
	char	**values;
}			t_env;

typedef struct s_data
{
	t_inputline	*i_line;
	t_cmds		*cmds;
	t_env		**envs;
	int			qty_env;
	int			fd;
}				t_data;

void	start_envs(t_data *data, char **env);
void	add_env(t_data *data, char *env_value);
void	remove_env(t_data *data, char *env_unset);
void	clear_envs(t_data *data);
t_env	*get_env(t_data *data, char *env);
char	*get_value_env_join(t_env *env);

// Precisa tirar isso daqui
// inputline.h
void	input_line(t_data *data);

// cmds.h
int		test_and_apply_bin(t_data *data, t_cmd *cmd);
// My alteration
int	execute_cmds(t_data *data, t_cmd *cmd, int i);
void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[]);
// finish
void	builtin_echo(t_cmd *builtin, int fd[]);
void	builtin_cd(t_cmd *builtin, int fd[]);
void	builtin_pwd(t_cmd *builtin, int fd[]);
void	builtin_export(t_data *data, t_cmd *builtin, int fd[]);
void	builtin_unset(t_data *data, t_cmd *builtin, int fd[]);
void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[]);
void	builtin_env(t_data *data, t_cmd *builtin, int fd[]);
#endif
