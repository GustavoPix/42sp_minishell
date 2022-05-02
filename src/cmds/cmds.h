/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:18:34 by glima-de          #+#    #+#             */
/*   Updated: 2022/05/02 20:14:00 by wjuneo-f         ###   ########.fr       */
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
	char	*doc_end;
	int		error;
	char	*file_out;
	char	*file_in;
	int		fd_file_in;
	int		fd_file_out;
	int		append_outfile;
}			t_cmd;

typedef struct s_cmds
{
	int		qty;
	// char	*file_in;
	// char	*file_out;
	// int		fd_file_in;
	// int		fd_file_out;
	// int		append_outfile;
	t_cmd	*first_cmd;
	t_cmd	*last_cmd;
}			t_cmds;

t_cmds	*start_cmds(void);
void	split_cmds(t_cmds *cmds, char *str);
void	clear_cmds(t_cmds *cmds, int all);
void	split_minnor_char(t_cmds *cmds);
int		has_double_signal(char *str, char c);
int		has_minnor_signal(char *str, char c);
int		has_char(char *str, char c);
void	swap_char_quote(char *str, int from, int to);
void	remove_quote(char *str);
int		count_size_matrix(char **str);
void	debug_cmds(t_cmds *cmds);
void	replace_char(char *str, int from, int to);
// My alteration
// finish
#endif
