/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:29:39 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:35:21 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* applied the function f to each character of the string passed
* as an argument, and passing its index as first argument.
* each char is passed by address to f to be modified 
* if it needs to be
*/

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (str == NULL || f == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		f(i, str + i);
		i++;
	}
}
