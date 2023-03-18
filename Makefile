CC= clang
CFLAGS=  -Wall -Wextra -Werror

NAME= ft_ping

HEADER= \
	include/ping.h \

SRC= \
	src/main.c \
	src/parsing.c \

OBJS = $(SRC:%.c=%.o)


%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
rel: $(NAME)

debug: CFLAGS+= -DDEBUG -g
debug: $(NAME)


$(NAME): $(OBJS)
	$(MAKE) -C ./libft/
	cp ./libft/libft.a ./
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. -lft

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

run: $(NAME)
	./$(NAME)

.PHONY: clean fclean re run debug