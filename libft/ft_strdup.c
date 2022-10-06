/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:58:28 by abartell          #+#    #+#             */
/*   Updated: 2022/03/14 22:01:13 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	char	*temp_dup;
	int		src_len;

	src_len = ft_strlen(src);
	dup = malloc(sizeof(*dup) * (src_len + 1));
	temp_dup = dup;
	while (*src)
	{
		*temp_dup = *src;
		src++;
		temp_dup++;
	}
	*temp_dup = 0;
	return (dup);
}
