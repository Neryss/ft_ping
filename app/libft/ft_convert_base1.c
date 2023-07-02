/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:26:35 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:45:15 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_base(char *base)
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

int	ft_int_from_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_is_in_base(char c, char *base)
{
	int	i;

	i = -1;
	while (base[++i])
		if (c == base[i])
			return (1);
	return (0);
}
