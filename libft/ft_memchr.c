/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:41:51 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/18 14:52:56 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;

	s1 = (unsigned char *)s;
	if (!n)
		return (NULL);
	while (*s1 != (unsigned char)c)
	{
		if (!(s1++) || n - 1 == 0)
			return (NULL);
		n--;
	}
	return (s1);
}
