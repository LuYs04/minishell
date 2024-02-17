/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:41:13 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/05 19:21:56 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)

{
	char	*cop;

	cop = (char *)s;
	while (*cop != '\0' && *cop != (char)c)
		cop++;
	if (*cop == (char)c)
		return (cop);
	return (0);
}
