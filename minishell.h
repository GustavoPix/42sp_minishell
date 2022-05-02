/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:54:58 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/02 20:13:55 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #define _GNU_SOURCE
# include "./libft/libft.h"
# include "./src/inputline/inputline.h"
# include "./src/path/path.h"
# include "./src/cmds/cmds.h"

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
	int			stdin_fd;
	int			exit_code;
}				t_data;

typedef struct s_action
{
	struct sigaction	sigaction;
}			t_action;

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
void	setup_cmds_bin_path(t_data *data);
// My alteration
int		execute_cmds(t_data *data, t_cmd *cmd, t_action *action);
void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[]);
// finish
void	builtin_echo(t_cmd *builtin, int fd[]);
void	builtin_cd(t_data *data, t_cmd *btin);
void	builtin_pwd(t_cmd *builtin, int fd[]);
void	builtin_export(t_data *data, t_cmd *builtin);
void	builtin_unset(t_data *data, t_cmd *builtin);
void	indentify_builtin(t_data *data, t_cmd *builtin, int fd[]);
void	builtin_env(t_data *data, t_cmd *builtin, int fd[]);

// minishell
int		loop_minishell(t_data *data, t_action *action);
int		set_env_value(t_data *data, char *key, char *value);
int		not_pipe_cmds(t_data *data, t_cmd *cmd);
void	initdups(t_data *data, t_cmd *cmd, int fd[]);

// exec
int		not_pipe_cmds(t_data *data, t_cmd *cmd);
int		not_fork_cmds(t_data *data, t_cmd *cmd);
int		ft_fdjoin(int fd1, int fd2);
#endif
