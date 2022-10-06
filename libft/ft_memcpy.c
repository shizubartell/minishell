/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:09:08 by abartell          #+#    #+#             */
/*   Updated: 2022/03/13 02:54:56 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srctemp;
	unsigned char	*desttemp;

	i = 0;
	srctemp = (unsigned char *)src;
	desttemp = (unsigned char *)dest;
	while (n > i)
	{
		desttemp[i] = srctemp[i];
		i++;
	}
	return (dest);
}
