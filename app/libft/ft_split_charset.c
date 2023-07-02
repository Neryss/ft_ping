/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:01:04 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 11:35:51 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	i;
	int	word;
	int	check;

	i = 0;
	word = 0;
	while (str[i])
	{
		check = 0;
		while (is_char_in_str(str[i], charset) && str[i])
			i++;
		while (!is_char_in_str(str[i], charset) && str[i])
		{
			i++;
			check = 1;
		}
		word += check;
	}
	return (word);
}

static int	get_word_length(char *str, char *charset, int index)
{
	int	l;

	l = 0;
	while (str[index] && !is_char_in_str(str[index], charset))
	{
		index++;
		l++;
	}
	return (l);
}

char	**ft_split_charset(char *str, char *charset)
{
	int		word_count;
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	k = 0;
	word_count = count_words(str, charset);
	tab = malloc(sizeof(char **) * word_count + 1);
	if (!tab)
		return (0);
	while (k < word_count)
	{
		j = 0;
		while (is_char_in_str(str[i], charset))
			i++;
		if (!ft_malloc(&tab[k], get_word_length(str, charset, i) + 1))
			return (ft_freeall(tab, k));
		while (str[i] && !(is_char_in_str(str[i], charset)))
			tab[k][j++] = str[i++];
		tab[k++][j] = '\0';
	}
	tab[k] = 0;
	return (tab);
}
