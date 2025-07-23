CC	= cc

CFLAGS	= -Wall -Wextra -Werror

SRC	=	main.c\
		pipex_exec.c\
		pipex_fork.c\
		libft_petit.c\

OBJ = ${SRC:.c=.o}

%.o:%.c
	${CC} ${CFLAGS} -c $^

NAME	= pipex.a

all : ${NAME}

${NAME} : ${OBJ}
	ar -rcs -o $@ $^

clean	:
	rm -f	main.c\
			pipex_exec.c\
			pipex_fork.c\
			libft_petit.c\

fclean	:	clean
	rm	-f	${NAME}

re	:	fclean
	make