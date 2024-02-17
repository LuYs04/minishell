/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:35:54 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 13:08:45 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	k;
	size_t	i;

	k = ft_strlen(src);
	if (!dst)
		return (ft_strlen(src));
	i = 0;
	if (size > 0)
	{
		while (src[i] && size - 1 > i)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (k);
}
