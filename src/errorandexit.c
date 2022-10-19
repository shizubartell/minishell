/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorandexit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:12:05 by abartell          #+#    #+#             */
/*   Updated: 2022/10/19 15:04:07 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	mini_exit(t_list *cmd, int *ex)
{
	t_node	*node;
	long	stat[2];

	node = cmd->content;
	*ex = !cmd->next;
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	stat[1] = ft_atoi(node->full_cmd[1]);
	if (node->full_cmd[2])
	{
		*ex = 0;
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
	}
	else if (stat[1] == -1)
	{
        ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	stat[0] %= 256 + 256 * (stat[0] < 0);
	return (stat[0]);
}