/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:51:54 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:34:39 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* locates the first occurrence of the NUL-terminated
* string needle in the string haystack where not more than
* len characters are searched
* example : haystack => goodhacker
*           needle => hack
* if needle is an empty string, haystack is returned
* if needle occurs nowhere, NULL is returned
* otherwise a pointer to the first char of the first
* occurence of needle is returned
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int		i;
	unsigned int		j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (i + j < len && haystack[i + j] == needle[j])
			{
				j++;
				if (!needle[j])
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (0);
}
