/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:03:51 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 14:07:02 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dest);
	k = i;
	j = 0;
	if (!dest)
		return (0);
	if (size < ft_strlen(dest))
		return (size + ft_strlen(src));
	if (size > 0)
	{
		while (size-- - 1 > k && src[j])
			dest[i++] = src[j++];
		dest[i] = '\0';
	}
	else
		return (ft_strlen(src));
	return (k + ft_strlen(src));
}
