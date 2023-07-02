/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:11:34 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 11:14:20 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	treat_nb(int nb)
{
	int	n;

	n = nb;
	if (n < 0)
		n = -n;
	return (n);
}

char	*ft_putnbr_base(int nb, char *base)
{
	long		n;
	int			i;
	int			base_len;
	char		*res;

	res = malloc(2096 * sizeof(char));
	n = treat_nb(nb);
	i = 0;
	base_len = ft_strlen(base);
	while (base[base_len])
		base_len++;
	if (ft_check_base(base) && base_len > 1)
	{
		while (n || i == 0)
		{
			res[i++] = base[n % base_len];
			n = n / base_len;
			res[i] = '\0';
		}
	}
	if (nb < 0)
		res[i++] = '-';
	res[i] = '\0';
	ft_rev_tab(res);
	return (res);
}
