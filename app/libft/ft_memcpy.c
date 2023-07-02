/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:38:48 by ckurt             #+#    #+#             */
/*   Updated: 2020/11/26 14:16:52 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*bdest;
	const char	*bsrc;

	bdest = dst;
	bsrc = src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*bdest++ = *bsrc++;
	return (dst);
}
