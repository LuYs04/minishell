/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:22:47 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 19:14:17 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	if (big == little)
		return ((char *)little);
	while (len > 0 && *big)
	{
		i = 0;
		while (*(big + i) == little[i] && *(big + i) && i < len)
		{
			i++;
			if (little[i] == '\0')
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
