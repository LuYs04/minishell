/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:29:26 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 14:16:31 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			if (set[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int	end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			if (set[j + 1] == '\0')
				return (i);
			j++;
		}
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;

	a = end(s1, set) - start(s1, set);
	if (!s1 && !set)
		return (NULL);
	if (!set || !*s1)
		return (ft_strdup(""));
	if (!*set)
		return (ft_strdup(s1));
	if (start(s1, set) == 0 && end(s1, set) == 0)
		return (ft_strdup(""));
	else
		return (ft_substr(s1, start(s1, set), a + 1));
	return (0);
}
