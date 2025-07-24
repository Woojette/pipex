CC	= cc

CFLAGS	= -Wall -Wextra -Werror

SRC	=	main.c \
		pipex_exec.c \
		pipex_fork.c \
		libft_petit.c

OBJ = ${SRC:.c=.o}

%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@

NAME	= pipex.a

all : ${NAME}

${NAME} : ${OBJ}
	ar -rcs $@ $^

clean	:
	rm -f	main.o \
			pipex_exec.o \
			pipex_fork.o \
			libft_petit.o

fclean	:	clean
	rm	-f	${OBJ}

re	:	fclean
	make