SRC		= $(wildcard ./*.c)

OBJS	= ${SRC:.c=.o}

NAME	= libft.a

CC 		= gcc
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
					

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

re:			fclean all

.PHONY:	all clean fclean re