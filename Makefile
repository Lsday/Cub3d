SRC = src/main.c

CC = gcc
OBJS = $(SRC:%.c=%.o)
NAME = cube

%.o: %.c
	$(CC) -g  -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -g $(OBJS) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	rm -rf ${OBJS}

fclean : clean
	rm ${NAME}

re : fclean ${NAME}	






