/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:51:39 by abartell          #+#    #+#             */
/*   Updated: 2022/11/05 21:10:14 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**splitter(char **av, t_prompt *get)
{
	char	**splitsubs;
	int		i;
	int		qs[2];

	i = -1;
	while (av && av[++i])
	{
		av[i] = expanding_vars(av[i], -1, qs, get);
		av[i] = pathexpander(av[i], -1, qs, \
			get_env_value("HOME", get->envp, 4));
		splitsubs = subcmd_chop(av[i], "<|>");
		replace_matrixline(&av, splitsubs, i);
		i = i + matrixlength(splitsubs) - 1;
		free_matrix(&splitsubs);
	}
	return (av);
}

static int	listsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

static void	*parsing(char **args, t_prompt *p)
{
	int	exit;
	int	i;

	exit = 0;
	p->cmds = fill_nodes(splitter(args, p), -1);
	if (!p->cmds)
		return (p);
	i = listsize(p->cmds);
	status = builtin_handler(p, p->cmds, &exit, 0);
	while (i-- > 0)
		waitpid(-1, &status, 0);
	if (!exit && status == 13)
		status = 0;
	if (status > 255)
		status = status / 255;
	if (args && exit)
	{
		ft_lstclear(&p->cmds, free_node);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_prompt *p)
{
	char	**i;
	t_node	*node;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	i = command_chop(out, " ");
	free(out);
	if (!i)
		errormsg(QUOTE, NULL, 1);
	if (!i)
		return ("");
	p = parsing(i, p);
	if (p && p->cmds)
		node = p->cmds->content;
	if (p && p->cmds && node && node->full_cmd && listsize(p->cmds) == 1)
		p->envp = set_env_value("_", node->full_cmd \
			[matrixlength(node->full_cmd) - 1], p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_node);
	return (p);
}
