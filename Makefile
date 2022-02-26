# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 19:29:25 by glima-de          #+#    #+#              #
#    Updated: 2022/02/26 16:49:01 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

LIBFT 		= libft

SRC			= ./src/inputline/path.c \
			  ./src/inputline/init.c \
			  ./src/inputline/inputline.c \
			  ./src/inputline/clear.c

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
			valgrind -q --leak-check=full ./${NAME}

.PHONY:		all gclone clean fclean re test val
