/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:44:10 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 15:27:55 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_atoi_len(char *str)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(str[i]) || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

int	ft_atof_len(char *str)
{
	int	len;

	len = ft_atoi_len(str);
	str += len;
	if (*str != '.')
		return (len);
	len += ft_atoi_len(str + 1) + 1;
	return (len);
}

double	ft_atof(char *str)
{
	double	ent;
	double	dec;
	size_t	i;
	int		neg;

	ent = ft_atoi(str);
	neg = 0;
	if (ent == 0)
	{
		i = 0;
		while (str[i] && i < ft_atoi_len(str))
			if (str[i++] == '-')
				neg++;
	}
	str += ft_atoi_len(str);
	if (*str != '.')
		return (ent);
	dec = ft_atoi(++str);
	dec /= ft_pow(10, ft_nblen(dec));
	if (ent < 0 || neg > 0)
		return (ent - dec);
	else
		return (ent + dec);
}
