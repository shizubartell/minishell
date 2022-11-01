/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iczarnie <iczarnie@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:33:56 by iczarnie          #+#    #+#             */
/*   Updated: 2022/10/19 13:33:56 by iczarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*initialise_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
    node->inputfile = STDIN_FILENO;
	node->outputfile = STDOUT_FILENO;
	node->full_cmd = NULL;
	node->full_path = NULL;
	return (node);
}

t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_node);
	free_matrix(&temp);
	free_matrix(&args);
	return (NULL);
}

void	free_node(void *content)
{
	t_node	*node;

	node = content;
    if (node->inputfile != STDIN_FILENO)
		close(node->inputfile);
	if (node->outputfile != STDOUT_FILENO)
		close(node->outputfile);
	free_matrix(&node->full_cmd);
	free(node->full_path);
	free(node);
}

static t_node	*choose_redirection(t_node *node, char **trimmed, int *i, char **args)
{
	if (trimmed[*i])
	{
		if (args[*i][0] == '<' && args[*i + 1] && args[*i + 1][0] == '<')
			node = get_infile2(node, trimmed, i);
		else if (args[*i][0] == '<')
			node = get_infile1(node, trimmed, i);
		else if (args[*i][0] == '>' && args[*i + 1] && args[*i + 1][0] == '>')
			node = get_outfile2(node, trimmed, i);
		else if (args[*i][0] == '>')
			node = get_outfile1(node, trimmed, i);
		else if (args[*i][0] != '|')
			node->full_cmd = addrowmatrix(node->full_cmd, trimmed[*i]);
		else
		{
			errormsg(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	errormsg(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

t_list	*fill_nodes(char **args, int i)
{
	t_list	*cmds[2];
	char	**trimmed;

	cmds[0] = NULL;
	trimmed = args_trimming(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(initialise_node()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		cmds[1]->content = choose_redirection(cmds[1]->content, trimmed, &i, args);
		if (i < 0)
			return (stop_fill(cmds[0], args, trimmed));
		if (!args[i])
			break ;
	}
	free_matrix(&trimmed);
	free_matrix(&args);
	return (cmds[0]);
}