/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:16:44 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:49:02 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_check_white_spaces(char *str, int i)
{
	while (str[i] == '\r' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\n' || str[i] == ' ')
		i++;
	return (i);
}