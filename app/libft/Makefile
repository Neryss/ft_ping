# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 13:34:22 by ckurt             #+#    #+#              #
#    Updated: 2021/03/31 12:48:28 by ckurt            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

_END=\033[0m
_BOLD=\033[1m
_UNDER=\033[4m
_REV=\033[7m

_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_PURPLE=\033[35m
_CYAN=\033[36m
_WHITE=\033[37m

_IGREY=\033[40m
_IRED=\033[41m
_IGREEN=\033[42m
_IYELLOW=\033[43m
_IBLUE=\033[44m
_IPURPLE=\033[45m
_ICYAN=\033[46m
_IWHITE=\033[47m

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -fno-builtin
INCS = libft.h
LIBC = ar rcs
NAME = libft.a
SRCS = ft_memset.c \
		ft_bzero.c \
		ft_memccpy.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strncat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_atoi.c \
		ft_strdup.c \
		ft_strndup.c \
		ft_calloc.c \
		ft_strjoin.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		ft_putstrl.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_split.c \
		ft_substr.c \
		ft_strtrim.c\
		ft_itoa.c \
		ft_itoa_base.c \
		ft_strmapi.c \
		ft_check_whitespaces.c \
		ft_strcat.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstclear.c \
		ft_foreach.c \
		ft_freeall.c \
		ft_isalnum.c \
		ft_split_charset.c \
		ft_convert_base1.c \
		ft_convert_base2.c \
		ft_putnbr_base.c \
		ft_atoi_base.c \
		ft_ischarset.c \
		ft_itoa_base_signed.c \
		ft_uitoa.c \
		ft_nblen.c \
		ft_is_in_str.c \
		ft_freetab.c \
		ft_read_file.c \
		ft_iswhitespace.c \
		ft_atof.c \
		ft_math_power.c \
		ft_startwith.c \
		ft_endwith.c \
		ft_skipuntilc.c \
		ft_strcmp.c \
		ft_rgbtohex.c \
		ft_malloc.c \
		ft_pow.c \
		ft_isinrange.c \
		ft_minmax.c \
		ft_clamp.c \
		ft_islinenum.c \
		ft_sort_int_tab.c
OBJS = $(SRCS:.c=.o)

.c.o:
	@printf "$(_PURPLE)[LIBFT] $(_END)$(_CYAN) [+]$(_END) Compiling $(_BLUE)owo$(_END) | $(_CYAN)$<$(_END)\n" | tr "lr" "w"
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@printf "$(_GREEN)[LIBFT][DONE] $(_END) Fiwniwshed uwu\n"

re: fclean
	@$(MAKE) all

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(libft.a)
	@printf "$(_RED)[LIBFT]  [-]$(_RED) $(_UNDER)All cleaned up now uwu!\n$(_END)" | tr "lr" "w"

count:
	@printf ".c files :"
	@find . -type f -name "*.c" | wc -l
	@printf ".o files :"
	@find . -type f -name "*.o" | wc -l

.PHONY: clean fclean re all