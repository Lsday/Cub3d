SRC = src/main.c

CC = gcc
OBJS = $(SRC:%.c=%.o)
NAME = cube
FLAGS = #-Werror -Wall -Werror

# #LINUX
# %.o: %.c
# 	$(CC) $(FLAGS) -g  -I/usr/include -Imlx_linux -O3   -c $< -o $@

# $(NAME): $(OBJS)
# 	$(CC) -g $(OBJS) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

#MACOS
%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -rf ${OBJS}

fclean : clean
	rm ${NAME}

re : fclean ${NAME}	






