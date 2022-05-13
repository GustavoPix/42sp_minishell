LIBFT         = ./libft/libft.a

SRC            = ./main.c \
              ./src/inputline/utils.c \
              ./src/inputline/path.c \
              ./src/inputline/init.c \
              ./src/inputline/inputline.c \
              ./src/inputline/clear.c \
              ./src/path/gofolder.c \
              ./src/cmds/init.c \
              ./src/cmds/split_cmds.c \
              ./src/cmds/clear.c \
              ./src/cmds/utils.c \
              ./src/cmds/utils2.c \
              ./src/cmds/utils3.c \
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

OBJS_SLG    = ${SRC:.c=.o}

UNAME        := $(shell uname)

CC             = gcc
CFLAGS        = -Wall -Wextra -Werror -g3
EFLAGS        = -lreadline
RM            = rm -f
NAME        = minishell

all:         ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I./libft

$(NAME):     $(LIBFT) ${OBJS_SLG} minishell.h
			$(CC) $(CFLAGS) $(OBJS_SLG) $(LIBFT) $(EFLAGS) -o $(NAME)

$(LIBFT):
			make -C ./libft

clean:
			make -C ./libft clean
			${RM} ${OBJS_SLG}

fclean:	 clean
			make -C ./libft fclean
			${RM} ${NAME}

re:		 fclean all

test:		all clean
			clear
			./${NAME}

val:		all clean
			clear
			valgrind -q --leak-check=full ./${NAME}

.PHONY:		all clean fclean re test val

