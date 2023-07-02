/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 11:19:36 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/20 11:20:03 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_dmax(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_dmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
