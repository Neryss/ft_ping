/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:14:50 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 16:03:59 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned long	temp;
	char			*substr;

	i = 0;
	temp = 0;
	substr = malloc(sizeof(char) * (len + 1));
	if (!s || !substr)
		return (0);
	while (s[i] && temp < len)
	{
		if (i >= start)
			substr[temp++] = s[i];
		i++;
	}
	substr[temp] = 0;
	return (substr);
}
