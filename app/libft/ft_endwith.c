/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:58:10 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:45:54 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endwith(char *str, char *end)
{
	size_t	lenstr;
	size_t	lenend;

	if (!str || !end)
		return (0);
	lenstr = ft_strlen(str);
	lenend = ft_strlen(end);
	if (lenend > lenstr)
		return (0);
	return (ft_strncmp(str + lenstr - lenend, end, lenend) == 0);
}
