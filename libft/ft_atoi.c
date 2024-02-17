/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgevor <armgevor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:27:29 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 19:15:48 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_exit(const char *ptr)
{
	int	nshan;
	int	i;
	int	tiv;

	tiv = 0;
	i = 0;
	nshan = 1;
	while (ptr[i] == '\t' || ptr[i] == '\n' || ptr[i] == '\v'
		|| ptr[i] == '\f' || ptr[i] == ' ' || ptr[i] == '\r')
		i++;
	if (ptr[i] == '+')
		i++;
	if (ptr[i] == '-')
	{
		nshan = -1;
		i++;
	}
	while (ptr[i] >= 48 && ptr[i] <= 57)
	{
		tiv = tiv * 10 + (ptr[i] - '0');
		i++;
	}
	if (ptr[i])
		return (255);
	return (nshan * tiv);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	q;

	res = 0;
	q = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		q++;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (q == 1)
		res *= -1;
	return (res);
}
