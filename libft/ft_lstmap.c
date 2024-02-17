/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:51:25 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 15:32:58 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*node;

	newlist = (void *)0;
	if (!lst || !del || !f)
		return (NULL);
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&newlist, del);
			free(newlist);
			return (NULL);
		}
		ft_lstadd_back(&newlist, node);
		lst = lst->next;
	}
	return (newlist);
}
