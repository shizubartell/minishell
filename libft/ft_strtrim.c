/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:38:13 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:34:30 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* strtrim removes all whitespace char from beginning
* and end of a str
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	char	*dest;

	if (!(s1 && set))
		return (NULL);
	front = 0;
	back = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (s1[back - 1] && ft_strchr(set, s1[back - 1]) && back > front)
		back--;
	dest = malloc(sizeof(char) * (back - front + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[front], back - front + 1);
	return (dest);
}
