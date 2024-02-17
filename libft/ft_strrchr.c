/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgevor <armgevor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:00:23 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/29 16:50:24 by armgevor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*s;

	s = (char *)str;
	if (s)
		i = ft_strlen(s);
	while (s && s[i] != (unsigned char)c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (s + i);
}
