/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:24:59 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:35:34 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_out(const char *s, char c)
{
	int	j;
	int	i;
	int	isstring;

	j = 0;
	i = 0;
	isstring = 0;
	while (s[j])
	{
		if (s[j] != c && isstring == 0)
		{
			isstring = 1;
			i++;
		}
		else
			isstring = 0;
		j++;
	}
	return (i);
}

static char	*outstr(const char *s, int start, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		string[i] = s[start];
		i++;
		start++;
	}
	string[i] = '\0';
	return (string);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		start;
	char	**out;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	start = -1;
	out = ft_calloc(sizeof(char *), (len_out(s, c) + 1));
	if (!out)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start == -1)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			out[j++] = outstr(s, start, i);
			start = -1;
		}
		i++;
	}
	return (out);
}
