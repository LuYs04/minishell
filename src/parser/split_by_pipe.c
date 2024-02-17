/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgevor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:53:44 by armgevor          #+#    #+#             */
/*   Updated: 2024/01/29 15:53:48 by armgevor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	count_pipes(char *line, int i, int w)
{
	char	q;

	while (line && line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
		}
		if (line[i] == '|')
			w++;
		if (line[i])
			i++;
	}
	return (w);
}

t_parse	*devider(char *line)
{
	t_parse	*split;
	t_parse	*temp;
	int		count;
	int		i;

	i = 0;
	split = NULL;
	count = count_pipes(line, 0, 0) + 1;
	while (count)
	{
		temp = malloc(sizeof(t_parse));
		if (!temp)
			return (NULL);
		temp->index = ft_calloc(1, sizeof(t_index));
		temp->fd_in = -1;
		temp->fd_out = -1;
		temp->next = NULL;
		temp->prev = NULL;
		i += args_split(&line[i], temp, 0, 0);
		ft_doublelist_add_back(&split, temp);
		count--;
	}
	return (split);
}

t_parse	*pipe_split(char *line)
{
	t_parse	*res;

	if (!line)
		return (NULL);
	res = devider(line);
	return (res);
}
