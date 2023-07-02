/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 09:49:40 by ckurt             #+#    #+#             */
/*   Updated: 2020/11/30 14:12:25 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	uc;
	unsigned long	i;

	str = (unsigned char *)s;
	uc = c;
	i = 0;
	while (i < n)
	{
		if (str[i] == uc)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
