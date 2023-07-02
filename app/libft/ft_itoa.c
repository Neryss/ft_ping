/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:50:40 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:52:15 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_getsize(int n)
{
	int			count;

	count = 0;
	if (n < 0)
		n *= -1;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			count;
	int			i;
	long int	tmp;

	tmp = n;
	count = ft_itoa_getsize(n);
	if (tmp < 0 || count == 0)
		count++;
	res = ft_calloc(count + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		res[i++] = '-';
	}
	while (count > i)
	{
		res[--count] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (res);
}
