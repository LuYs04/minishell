/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:44:21 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/31 19:55:33 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	ft_doublelist_add_back(t_parse **lst, t_parse *new)
{
	t_parse	*a;

	a = (*lst);
	if (lst && new)
	{
		if (!*lst)
		{
			*lst = new;
			(*lst)->next = NULL;
			(*lst)->prev = NULL;
			return ;
		}
		while (a && a -> next)
			a = a -> next;
		a -> next = new;
		new->prev = a;
	}
}

void	free_node(t_parse *input_node)
{
	t_parse	*tmp;

	while (input_node)
	{
		tmp = input_node;
		tmp->operator = NULL;
		tmp->cmd = NULL;
		tmp->file = NULL;
		tmp->delim = NULL;
		tmp->index = NULL;
		input_node = input_node->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_input(t_parse *input_var, t_parse *input_node)
{
	t_parse	*tmp;

	while (input_var)
	{
		tmp = input_var;
		free2d(tmp->operator);
		free2d(tmp->cmd);
		free2d(tmp->file);
		free2d(tmp->delim);
		free(tmp->index);
		tmp->index = NULL;
		input_var = input_var->next;
		free(tmp);
		tmp = NULL;
	}
	free_node(input_node);
}
