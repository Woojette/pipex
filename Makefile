CC	= cc

CFLAGS	= -Wall -Wextra -Werror

SRC	=	test7.c\
		pipex_exec.c\
		pipex_commande.c\
		libft_petit.c\

OBJ = ${SRC:.c=.o}

%.o:%.c
	${CC} ${CFLAGS} -c $^

NAME	= pipex.a

all : ${NAME}

${NAME} : ${OBJ}
	ar -rcs -o $@ $^

clean	:
	rm -f	test7.c\
			pipex_exec.c\
			pipex_commande.c\
			libft_petit.c\

fclean	:	clean
	rm	-f	${NAME}

re	:	fclean
	make