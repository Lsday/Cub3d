SRC = src/main.c GetNextLine/get_next_line_utils.c GetNextLine/get_next_line.c src/parsing.c

CC = gcc
OBJS = $(SRC:%.c=%.o)
NAME = cube
FLAGS = -g -Werror -Wall -Werror
LIBFT = ./libft/libft.a

all:	$(NAME)

# #LINUX
%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux  -c $< -o $@

#-O3

$(NAME):  $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT)  -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

#MACOS
# %.o: %.c
# 	$(CC) $(FLAGS) -Imlx -c $< -o $@

# $(NAME): $(OBJS)
# 	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)


 
$(LIBFT):
	$(MAKE) -C libft

clean :
	$(MAKE) -C libft clean
	rm -rf ${OBJS}

fclean : clean
	$(MAKE) -C libft fclean
	rm ${NAME}

re : fclean ${NAME}	






