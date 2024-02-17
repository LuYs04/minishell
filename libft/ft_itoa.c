/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:09:59 by luatshem          #+#    #+#             */
/*   Updated: 2023/02/18 15:11:49 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	n_count(long *j, long n)
{
	int	q;

	q = 1;
	if (n < 0)
	{
		n *= -1;
		q++;
	}
	while (n / *j != 0)
	{
		*j *= 10;
		q++;
	}
	return (q);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	long	j;
	long	nb;

	nb = (long)n;
	j = 10;
	s = (char *)malloc((n_count(&j, nb) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	j /= 10;
	if (nb < 0)
	{
		s[i++] = '-';
		nb *= -1;
	}
	while (j != 0)
	{
		s[i++] = (nb / j) + '0';
		nb %= j;
		j /= 10;
	}
	s[i] = '\0';
	return (s);
}
