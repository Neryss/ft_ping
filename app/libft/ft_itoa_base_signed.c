/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_signed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:02:05 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 11:02:23 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_itoa_getsize_base(long long n, int base_len)
{
	int		count;

	count = 0;
	while (n)
	{
		n /= base_len;
		count++;
	}
	return (count);
}

char	*ft_itoa_base_signed(long long n, char *base)
{
	int		count;
	int		base_len;
	char	*res;

	base_len = ft_strlen(base);
	count = ft_itoa_getsize_base(n, base_len);
	res = ft_calloc(count + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (count > 0)
	{
		res[--count] = base[n % base_len];
		n /= base_len;
	}
	return (res);
}
