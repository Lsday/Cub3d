SRC = src/main.c src/GetNextLine/get_next_line_utils.c src/GetNextLine/get_next_line.c src/parsing.c

CC = gcc
OBJS = $(SRC:%.c=%.o)
NAME = cube
FLAGS = -g #-Werror -Wall -Werror

# #LINUX
# %.o: %.c
# 	$(CC) $(FLAGS) -g  -I/usr/include -Imlx_linux -O3   -c $< -o $@

# $(NAME): $(OBJS)
# 	$(CC) -g $(OBJS) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

#MACOS
%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -rf ${OBJS}

fclean : clean
	rm ${NAME}

re : fclean ${NAME}	






