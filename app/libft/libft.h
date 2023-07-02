/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:49:05 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/26 11:55:57 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

char				**ft_split(char const *s, char c);
char				**ft_split_charset(char *str, char *charset);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);

char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncat(char *dest, char *src, unsigned int nb);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_putnbr_base(int nb, char *base);
char				*ft_itoa(int n);
char				*ft_itoa_base(size_t n, char *base);
char				*ft_itoa_base_signed(long long n, char *base);
char				*ft_uitoa(unsigned int nb);
char				*ft_free_strjoin(char *s1, char *s2);
char				**ft_read_file(int fd);
void				*ft_memset(void *str, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_freeall(char **tab, int size);
void				*ft_freetab(char **tab);
void				*ft_malloc(char **ret, size_t size);
void				ft_putendl_fd(char *s, int fd);
void				ft_putendl(char *s);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_bzero(void *s, size_t n);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_foreach(int *tab, int length, void (*f)(int));
void				ft_swap(void *a, void *b);
void				ft_rev_tab(char *tab);
void				ft_sort_int_tab(int *tab, int size);
int					ft_putchar(char c);
int					ft_putstr_fd(char *s, int fd);
int					ft_putchar_fd(char c, int fd);
int					ft_putstr(char *s);
int					ft_putstrl(char *str, int len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_is_in_base(char c, char *base);
int					ft_is_in_str(const char *s, int c);
int					ft_check_base(char *base);
int					ft_int_from_base(char c, char *base);
int					ft_atoi_base(char *str, char *base);
size_t				ft_atoi_len(char *str);
int					ft_atof_len(char *str);
int					ft_lstsize(t_list *lst);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isinrange(long nb, long min, long max);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_iswhitespace(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_gnl(int fd, char **line);
double				ft_dmin(double a, double b);
double				ft_dmax(double a, double b);
int					imin(int a, int b);
int					imax(int a, int b);
int					ft_atoi(const char *str);
int					ft_check_white_spaces(char *str, int i);
int					ft_ischarset(char c, const char *str);
int					get_next_line(int fd, char **line);
int					ft_endwith(char *str, char *end);
int					ft_startwith(char *str, char *start);
int					ft_skipuntilc(char *str, char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_islinenum(char *str);
long long			ft_math_power(long long nb, long long power);
long long			ft_pow(long long nb, long long n);
double				ft_atof(char *str);
unsigned long		ft_rgbtohex(int r, int g, int b);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_nblen(int n);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
