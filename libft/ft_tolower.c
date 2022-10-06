/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:25:13 by abartell          #+#    #+#             */
/*   Updated: 2022/03/14 22:03:52 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* simply putting upper char to lower char
* via ASCII table incrementing
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	c = c + 32;
	return (c);
}
