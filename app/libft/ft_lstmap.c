/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:45:33 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 10:58:13 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstmap_lstnew(void *content)
{
	t_list		*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

static void	ft_lstmap_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = temp;
		}
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*first;

	res = ft_lstmap_lstnew(lst->content);
	if (!lst || !(res))
	{
		ft_lstmap_lstclear(&lst, del);
		return (NULL);
	}
	first = res;
	while (lst->next != NULL)
	{
		res->content = f(lst->content);
		lst = lst->next;
		res->next = ft_lstmap_lstnew(f(lst->content));
		if (!res->next)
		{
			ft_lstmap_lstclear(&first, del);
			return (NULL);
		}
		res = res->next;
	}
	return (first);
}
