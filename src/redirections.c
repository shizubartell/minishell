/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:40:42 by iczarnie          #+#    #+#             */
/*   Updated: 2022/11/01 14:42:27 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//covers for errors in redirections
void	error_in_redirections(int *i, int file_descriptor)
{
	char	*nl;

	nl = "minishell: syntax error near unexpected token `newline'";
	*i = -1;
	if (file_descriptor != -1)
	{
		ft_putendl_fd(nl, 2);
		status = 2;
	}
	else
		status = 1;
}

// > condition, if that is possible creates a file (every time new)
// + adds content
t_node	*get_outfile1(t_node *node, char **args, int *i)
{	
	(*i)++;
	if (args[*i])
	{
		if (node->outputfile > 2)
			close(node->outputfile);
		if (access(args[*i], W_OK) == -1 && access(args[*i], F_OK) == 0)
			errormsg(NOPERM, args[*i], 126);
		node->outputfile = open(args[*i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	if (!args[*i] || node->outputfile == -1)
		error_in_redirections(i, node->outputfile);
	return (node);
}

// >> condition, appends to the file if possible
t_node	*get_outfile2(t_node *node, char **args, int *i)
{
	(*i)++;
	if (args[++(*i)])
	{
		if (node->outputfile > 2)
			close(node->outputfile);
		if (access(args[*i], W_OK) == -1 && access(args[*i], F_OK) == 0)
			errormsg(NOPERM, args[*i], 126);
		node->outputfile = open(args[*i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	if (!args[*i] || node->outputfile == -1)
		error_in_redirections(i, node->outputfile);
	return (node);
}

// < condition
t_node	*get_infile1(t_node *node, char **args, int *i)
{
	(*i)++;
	if (args[*i])
	{
		if (node->inputfile > 2)
			close(node->inputfile);
		if (access(args[*i], F_OK) == -1)
			errormsg(NODIR, args[*i], 127);
		else if (access(args[*i], R_OK) == -1)
			errormsg(NOPERM, args[*i], 126);
		node->inputfile = open(args[*i], O_RDONLY);
	}
	if (!args[*i] || node->inputfile == -1)
		error_in_redirections(i, node->inputfile);
	return (node);
}
