/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:02:55 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:41:31 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calcul_res(int res, int neg, int pos)
{
	if (neg == 0)
		return (res);
	if (pos == 0 && neg == 1)
		return (-res);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	pos;
	int	res;

	neg = 0;
	pos = 0;
	res = 0;
	i = ft_check_white_spaces((char *)str, 0);
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			neg++;
		else
			pos++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if ((pos >= 0 && pos <= 1) && (neg >= 0 && neg <= 1))
		return (calcul_res(res, neg, pos));
	return (0);
}
