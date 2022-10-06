/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:36:27 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:34:22 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Allocates (with malloc(3)) and returns a substring
* from the string ’s’.
* The substring begins at index ’start’ and is of
* maximum size ’len’.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	size;

	if (s == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	if (start >= size || !s)
		len = 0;
	else if (size < (start + len))
		len = size - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
