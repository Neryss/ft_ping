CC= gcc
CFLAGS= -g -fsanitize=address -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory -j

NAME= ft_ping

HEADER= \
	include/ping.h \

SRC= \
	src/main.c \
	src/parsing.c \
	src/utils.c \
	src/packets.c \
	src/ping.c \

OBJS = $(SRC:%.c=%.o)


%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
rel: $(NAME)

debug: CFLAGS+= -DDEBUG -g
debug: all

./libft/libft.a:
	@make -C ./libft/

$(NAME): $(OBJS) ./libft/libft.a
	@cp ./libft/libft.a ./
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lm -L. -lft

clean:
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft/ fclean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

run: $(NAME)
	sudo ./$(NAME) google.com

valgrind: $(NAME)
	sudo valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME) google.com

.PHONY: clean fclean re run debug