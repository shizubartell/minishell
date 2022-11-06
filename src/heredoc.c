/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iczarnie <iczarnie@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:49:55 by iczarnie          #+#    #+#             */
/*   Updated: 2022/10/27 10:49:55 by iczarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//joins the things that were added in following lines
static char	*combining_strings(char *str[4], size_t len)
{
	char	*temp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], str[2], len) \
		|| ft_strlen(str[2]) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(temp, str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", str[3], str[2]);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(temp, "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

//manages file descriptors for heredoc
static int	here_doc(char *str[4])
{
	int		fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		errormsg(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = combining_strings(str, 0);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}

//heredoc << condition
t_node	*get_infile2(t_node *node, char **args, int *i)
{
	char	*str[4];

	str[0] = NULL;
	str[1] = NULL;
	str[2] = NULL;
	str[3] = "minishell: warning: here-document delimited by end-of-file";
	(*i)++;
	if (args[++(*i)])
	{
		str[2] = args[*i];
		node->inputfile = here_doc(str);
	}
	if (!args[*i] || node->inputfile == -1)
		error_in_redirections(i, node->inputfile);
	return (node);
}
