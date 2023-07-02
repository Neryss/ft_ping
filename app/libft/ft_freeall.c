/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:04:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:46:09 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_freeall(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
	return (NULL);
}
