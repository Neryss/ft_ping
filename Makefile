CC= clang
CFLAGS=  -Wall -Wextra -Werror

NAME= ft_ping

HEADER= \

SRC= \
	src/main.c \


OBJS = $(SRC:%.cpp=%.o)


%.o: %.cpp Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
rel: $(NAME)

debug: CFLAGS+= -DDEBUG -g
debug: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

run: $(NAME)
	./$(NAME)

.PHONY: clean fclean re run debug