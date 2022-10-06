/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:53:27 by abartell          #+#    #+#             */
/*   Updated: 2022/03/15 15:38:17 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		tmp = *lst;
		*lst = tmp->next;
		free(tmp);
	}
	*lst = NULL;
}
