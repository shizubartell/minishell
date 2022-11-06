/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:42:17 by abartell          #+#    #+#             */
/*   Updated: 2022/11/06 16:57:30 by abartell         ###   ########.fr       */
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
	if (!ft_strncmp(*node->full_cmd, "export", i) && i == 6)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "unset", i) && i == 5)
		return (1);
	return (0);
}

//handles all the builtins
int	builtin_handler(t_prompt *prompt, t_list *cmd, int *exit, int n)
{
	char	**i;

	while (cmd)
	{
		i = ((t_node *)cmd->content)->full_cmd;
		n = 0;
		if (i)
			n = ft_strlen(*i);
		if (n && !ft_strncmp(*i, "exit", n) && n == 4)
			g_status = exitpath(cmd, exit);
		if (!cmd->next && i && !ft_strncmp(*i, "cd", n) && n == 2)
			g_status = cding(prompt);
		else if (!cmd->next && i && !ft_strncmp(*i, "export", n) && n == 6)
			g_status = export(prompt);
		else if (!cmd->next && i && !ft_strncmp(*i, "unset", n) && n == 5)
			g_status = unset(prompt);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			ex_nocmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}
