/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:48:29 by abartell          #+#    #+#             */
/*   Updated: 2022/03/14 16:15:11 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* if c is part of printable ASCII table characters give a
* output, otherwise return nothing
*/

int	ft_isprint(int c)
{
	if (!((c >= 32 && c <= 126)))
	{
		return (0);
	}
	return (1);
}
