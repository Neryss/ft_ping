/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:13:34 by ckurt             #+#    #+#             */
/*   Updated: 2020/11/26 13:27:19 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*bdst;
	unsigned char	*bsrc;

	bdst = (unsigned char *)dst;
	bsrc = (unsigned char *)src;
	while (n--)
	{
		*bdst = *bsrc;
		if (*bsrc == (unsigned char)c)
			return (bdst + 1);
		bdst++;
		bsrc++;
	}
	return (NULL);
}
