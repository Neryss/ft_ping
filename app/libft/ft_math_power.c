/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_power.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:41:20 by ckurt             #+#    #+#             */
/*   Updated: 2021/01/26 15:28:08 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_math_power(long long nb, long long power)
{
	if (power < 0)
		return (0);
	if (power < 1)
		return (1);
	else
		return (nb * ft_math_power(nb, power - 1));
}
