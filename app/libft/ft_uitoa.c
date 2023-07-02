/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:49:04 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 16:03:06 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_getsize(unsigned int n)
{
	int			count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_uitoa(unsigned int nb)
{
	char		*res;
	long int	n;
	int			count;

	n = (long)nb;
	count = ft_itoa_getsize(n);
	if (count == 0)
		count++;
	res = ft_calloc(count + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (count)
	{
		res[--count] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
