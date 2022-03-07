# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 19:29:25 by glima-de          #+#    #+#              #
#    Updated: 2022/03/05 17:58:56 by wjuneo-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_PATH	= libraries/libft
LIBFT		= $(LIBFT_PATH)/libft.a

SOURCE_FILES = builtin_cd.c builtin_echo.c builtin_env.c builtin_export.c \
			   builtin_pwd.c builtin_unset.c exec_comand.c minishell.c \
			   start_shell.c

OBJ_PATH	 = objects
PATH_SOURCES = sources
SOURCES_MS	 = $(addprefix $(PATH_SOURCES)/, $(SOURCE_FILES))
OBJ_SOURCES  = $(SOURCES_MS:$(PATH_SOURCES)/%.c=$(OBJ_PATH)/%.o)

HEADER		= $(PATH_SOURCES)/minishell.h
NAME		= minishell

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -rf

$(OBJ_PATH)/%.o:	$(PATH_SOURCES)/%.c
					$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ_PATH) $(OBJ_SOURCES) $(HEADER)
			$(CC) $(CFLAGS) $(OBJ_SOURCES) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_PATH)
			$(MAKE) -C $(LIBFT_PATH) bonus

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			$(MAKE) -C $(LIBFT_PATH) clean
			$(RM) $(OBJ_PATH)

fclean:		clean
			$(MAKE) -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:			clean fclean all .c.o
