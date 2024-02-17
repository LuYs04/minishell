/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:13:59 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/30 16:58:19 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s_1;
	unsigned char	*s_2;
	size_t			i;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	i = 0;
	while (s_1 && s_2 && s_1[i] && s_2[i]
		&& s_1[i] == s_2[i] && i < n)
		i++;
	if (s_1 && s_2
		&& i < n)
		return (s_1[i] - s_2[i]);
	return (0);
}
