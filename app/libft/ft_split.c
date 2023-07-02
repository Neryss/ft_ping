/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 08:53:38 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 11:27:17 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	words;
	int	check;

	i = 0;
	words = 0;
	while (str[i])
	{
		check = 0;
		while ((str[i] == c) && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			i++;
			check = 1;
		}
		words += check;
	}
	return (words);
}

static int	get_word_length(char *str, char c, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	k = 0;
	wcount = count_words((char *)s, c);
	tab = malloc(sizeof(char **) * (wcount + 1));
	if (!tab)
		return (0);
	while (k < wcount)
	{
		j = 0;
		while (s[i] == c)
			i++;
		if (!ft_malloc(&tab[k], get_word_length((char *)s, c, i) + 1))
			return (ft_freeall(tab, k));
		while (s[i] != c && s[i])
			tab[k][j++] = s[i++];
		tab[k++][j] = '\0';
	}
	tab[k] = 0;
	return (tab);
}
