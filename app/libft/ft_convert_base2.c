/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:26:51 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/10 11:09:56 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b)
{
	void	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	ft_rev_tab(char *tab)
{
	int	i;
	int	size;

	size = 0;
	while (tab[size])
		size++;
	i = size / 2;
	while (--i >= 0)
		ft_swap(&tab[i], &tab[size - 1 - i]);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	if (ft_check_base(base_from) == 1 && ft_check_base(base_to) == 1)
		return (ft_putnbr_base(ft_atoi_base(nbr, base_from), base_to));
	return (NULL);
}
