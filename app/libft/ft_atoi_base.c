/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:27:20 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:42:16 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *str, char *base)
{
	int	res;
	int	i;
	int	neg;

	res = 0;
	i = 0;
	neg = 1;
	if (!ft_check_base(base))
		return (0);
	while (str[i] == '\r' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\n' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg *= -1;
	while (ft_is_in_base(str[i], base))
		res = res * ft_strlen(base) + ft_int_from_base(str[i++], base);
	return (res * neg);
}
