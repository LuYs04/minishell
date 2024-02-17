/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgevor <armgevor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:33:32 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/29 05:06:15 by armgevor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isalnum(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (!NULL);
	else if ((arg >= 65 && arg <= 90) || (arg >= 97 && arg <= 122))
		return (!NULL);
	else
		return (0);
}
