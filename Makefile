SRCS = ./src/main.c ./src/manage_memory_leak.c ./src/move_player.c \
       ./src/my_window.c ./src/opportunity_to_all_elements.c ./src/parcing.c
OBJS = $(SRCS:.c=.o)
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
LFLAGS =  -L/usr/include/minilibx-linux -lmlx -lXext -lX11
RM = rm -f
NAME = so_long
GET = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
PRINT = ./ft_printf/libftprintf.a
LIBFT = ./libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	make -C ./ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(GET) $(PRINT) $(LIBFT) -o $(NAME)

clean:
	make clean -C ./libft
	make clean -C ./ft_printf
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./libft
	make fclean -C ./ft_printf
	$(RM) $(NAME)

re: fclean all
