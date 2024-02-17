/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:52:08 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 15:33:20 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*start;

	start = *lst;
	p = (void *)0;
	if (!del || !*lst)
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		p = *lst;
		*lst = (*lst)->next;
		if (p != start)
			free(p);
	}
	start->next = NULL;
	free(start);
}
