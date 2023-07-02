/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:10:24 by ckurt             #+#    #+#             */
/*   Updated: 2020/11/24 14:05:36 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	slen;

	slen = ft_strlen(s);
	while (slen >= 0)
	{
		if (s[slen] == (char)c)
			return ((char *)&s[slen]);
		slen--;
	}
	return (NULL);
}
