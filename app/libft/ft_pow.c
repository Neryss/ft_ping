/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:28:38 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 12:20:26 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_pow(long long nb, long long power)
{
	if (power < 0)
		return (0);
	if (power < 1)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}
