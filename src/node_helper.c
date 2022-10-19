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
