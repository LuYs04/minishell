/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:11:09 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/18 15:10:04 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	a;
	char	*t;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1) + ft_strlen(s2);
	t = malloc((a + 1) * sizeof(char));
	if (!t)
		return (NULL);
	while (*s1)
	{
		*t = *s1;
		t++;
		s1++;
	}
	while (*s2)
	{
		*t = *s2;
		t++;
		s2++;
	}
	*t = '\0';
	return (t - a);
}
