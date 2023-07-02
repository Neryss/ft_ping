/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:14:59 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:53:54 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (0);
	while (base[++i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == '\r'
			|| base[i] == '\v' || base[i] == '\t' || base[i] == '\f'
			|| base[i] == ' ')
			return (0);
		while (base[i + j] != '\0')
			if (base[i] == base[i + j++])
				return (0);
		j = 1;
	}
	return (1);
}

static	int	ft_itoa_getsize_base(size_t n, int base_len)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= base_len;
		count++;
	}
	if (count == 0)
		count++;
	return (count);
}

char	*ft_itoa_base(size_t n, char *base)
{
	int		count;
	int		base_len;
	char	*res;

	base_len = ft_strlen(base);
	count = ft_itoa_getsize_base(n, base_len);
	res = ft_calloc(count + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		count = 0;
	}
	while (count > 0)
	{
		res[--count] = base[n % base_len];
		n /= base_len;
	}
	return (res);
}
