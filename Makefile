SRCS = fractal.c fractol.c k_hook.c birdy.c chooseurfighter.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

NAME = fractol

LIBS = libft/libft.a\

all: $(NAME)

$(NAME): $(OBJS)
		make -C ./libft
		make -C ./minilibx_macos
		$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME) -framework OpenGL -framework AppKit -I minilibx_macos ./minilibx_macos/libmlx.a
%.o: %.c
	gcc $< $(CFLAGS) -c -o $@

clean:
		rm -rf $(OBJS)
		make -C ./libft clean
		make -C ./minilibx_macos clean 
fclean: clean
		rm -rf $(NAME)
		make -C ./libft fclean

re: fclean all
