/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:30:06 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/18 14:54:30 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	size_t		i;

	i = 0;
	d = dest;
	if (src == dest)
		return (dest);
	while (i < n)
	{
		d[i] = ((char *)(src))[i];
		i++;
	}
	return (d);
}
