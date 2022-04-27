# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 19:29:25 by glima-de          #+#    #+#              #
#    Updated: 2022/04/27 12:47:33 by wjuneo-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

LIBFT 		= libft

SRC			= ./src/inputline/path.c \
			  ./src/inputline/init.c \
			  ./src/inputline/inputline.c \
			  ./src/inputline/clear.c \
			  ./src/path/gofolder.c \
			  ./src/cmds/init.c \
			  ./src/cmds/split_cmds.c \
			  ./src/cmds/clear.c \
			  ./src/cmds/utils.c \
			  ./src/cmds/get_inoutfile.c \
			  ./src/cmds/execute_cmds.c \
			  ./src/cmds/initdups.c \
			  ./src/cmds/aux_files.c \
			  ./src/builtin/builtin_cd.c \
			  ./src/builtin/builtin_echo.c \
			  ./src/builtin/builtin_env.c \
			  ./src/builtin/builtin_export.c \
			  ./src/builtin/builtin_pwd.c \
			  ./src/builtin/builtin_unset.c \
			  ./src/cmds/binpath.c \
			  ./src/cmds/treatments.c \
			  ./src/envs/init.c \
			  ./src/envs/clear.c \
			  ./src/envs/get_env_var.c \
			  ./src/envs/set_env.c \
			  ./src/minishell/minishell.c \
			  ./src/signals/signals.c

OBJS_SLG	= ${SRC:.c=.o}

UNAME		:= $(shell uname)

PATH_MLX	= mlx
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
EFLAGS		= -L/usr/include -lreadline
RM			= rm -f
NAME		= minishell

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -I libft -Imlx -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS) ${OBJS_M} ${OBJS_SLG}
			make -C $(LIBFT)
			${CC} -g $(CFLAGS) ${EFLAGS} -o $(NAME) $(OBJS) ${OBJS_M} ${OBJS_SLG} -L $(LIBFT) -lft

clean:
			make -C $(LIBFT) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_SLG}

fclean: 	clean
			make -C $(LIBFT) fclean
			${RM} ${NAME}

re: 		fclean all

test:		all clean
			clear
			./${NAME}

val:		all clean
			clear
			valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

.PHONY:		all clean fclean re test val

# valgrind -q --leak-check=full --track-fds=yes ./${NAME}

