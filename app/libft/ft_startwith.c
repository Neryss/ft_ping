/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startwith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:56:56 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 11:28:51 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_startwith(char *str, char *start)
{
	size_t	lenstr;
	size_t	lenstart;

	if (!str || !start)
		return (0);
	lenstr = ft_strlen(str);
	lenstart = ft_strlen(start);
	if (lenstart > lenstr)
		return (0);
	return (ft_strncmp(str, start, lenstart) == 0);
}
