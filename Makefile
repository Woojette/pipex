CC	= cc

CFLAGS	= -Wall -Wextra -Werror

SRC	=	main.c \
		pipex_exec.c \
		pipex_fork.c \
		libft_petit.c \
		libft_split.c

OBJ = ${SRC:.c=.o}

%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@

NAME	= pipex.a

all : ${NAME}

${NAME} : ${OBJ}
	ar -rcs $@ $^

clean	:
	rm -f	${OBJ}

fclean	:	clean
	rm	-f	${NAME}

re	:	fclean
	make

.PHONY: all clean fclean re
