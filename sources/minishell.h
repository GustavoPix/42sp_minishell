# ifndef MINISHELL_H
# define MINISHELL_H

#include "../libraries/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

# define clear() printf("\033[H\033[J")

int		main(int argc, char *argv[], char *envp[]);
int		minishell(char *envp[]);
char	*start_shell();


/////////////////
//////Exec///////
////////////////
int		exec_comands(char	**comand, int indentify, char *envp[]);
void	exec_builtin_child(char **comand, int fd[], char *envp[]);

/////////////////
/////BUILTIN/////
/////////////////
// void	indentify_builtin(char	**comand, int fd[], char *envp[]);
void	builtin_echo(char **comand, int fd[]);
void	builtin_cd(char	**comand, int fd[]);
void	builtin_pwd(char **comand, int fd[]);
void	builtin_export(char **comand, int fd[], char *envp[]);
void	builtin_unset(char **comand, int fd[], char *envp[]);
void	builtin_env(char **comand, int fd[], char *envp[]);
#endif
