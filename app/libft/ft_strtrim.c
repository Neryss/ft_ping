/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:10:11 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 16:04:36 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_trimmed_len(char const *s1, char const *set)
{
	int			i;
	int			j;
	int			len;
	int			tlen;

	i = 0;
	len = ft_strlen(s1);
	j = len - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > 0 && ft_strchr(set, s1[j]))
	{
		j--;
		i++;
	}
	tlen = len - i;
	if (tlen <= 0)
		return (0);
	return (tlen);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			tlen;
	int			i;
	int			j;
	char		*tstr;

	i = 0;
	j = 0;
	tlen = get_trimmed_len(s1, set);
	tstr = malloc(sizeof(char) * (tlen + 1));
	if (!tstr)
		return (0);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j < tlen)
	{
		tstr[j] = s1[i];
		j++;
		i++;
	}
	tstr[j] = 0;
	return (tstr);
}
