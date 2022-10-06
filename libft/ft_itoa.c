/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:33:28 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:38:30 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* itoa converts integer n into a character string
* the string is placed in the buffer passed
* which must be large enough to hold the output
*/

static int	ft_len(long long_n)
{
	int		len;

	len = 0;
	if (long_n <= 0)
		len++;
	while (long_n)
	{
		long_n = long_n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	nb;

	nb = n;
	len = ft_len(nb);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	else if (nb == 0)
		result[0] = '0';
	while (nb)
	{
		len--;
		result[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (result);
}
