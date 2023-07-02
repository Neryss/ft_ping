/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:01:18 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 16:07:44 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fstr;
	int		tlen;

	tlen = ft_strlen(s1) + ft_strlen(s2);
	fstr = ft_calloc(tlen + 1, sizeof(char));
	if (!fstr)
		return (NULL);
	fstr = ft_memcpy(fstr, s1, ft_strlen(s1));
	fstr = ft_strcat(fstr, (char *)s2);
	return (fstr);
}
