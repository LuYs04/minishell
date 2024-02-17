/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:58:26 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/19 14:44:56 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (src == dst)
		return (dst);
	if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	else if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			((char *)dst)[i - 1] = ((char *)src)[i - 1];
			i--;
		}
	}
	return (dst);
}
