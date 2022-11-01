/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:42:17 by abartell          #+#    #+#             */
/*   Updated: 2022/11/01 15:29:51 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if the first element in full_cmd is a builtin
int	builtins(t_node *node)
{
	int	i;

	if (!node->full_cmd)
		return (0);
	if ((node->full_cmd && ft_strchr(*node->full_cmd, '/')) || \
		(node->full_path && ft_strchr(node->full_path, '/')))
		return (0);
	i = ft_strlen(*node->full_cmd);
	if (!ft_strncmp(*node->full_cmd, "pwd", i) && i == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "echo", i) && i == 4)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "env", i) && i == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "exit", i) && i == 4)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "cd", i) && i == 2)
		return (1);
	return (0);
}
