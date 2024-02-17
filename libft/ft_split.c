/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:38:40 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 14:41:01 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char const *s, char c)
{
	int	i;
	int	j;
	int	t;

	j = 0;
	i = 0;
	t = 0;
	while (s[j])
	{
		if (s[j] != c && t == 0)
		{
			t = 1;
			i++;
		}
		else if (s[j] == c)
			t = 0;
		j++;
	}
	return (i);
}

void	check_repeat(char const *s, char c, int *i)
{
	while (s[*i] == c)
		(*i)++;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		j;
	int		start;

	if (!s)
		return ((char **) NULL);
	array = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < count(s, c))
	{
		check_repeat(s, c, &i);
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		array[j++] = ft_substr(s, start, i - start);
	}
	array[j] = NULL;
	return (array);
}
