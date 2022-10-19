/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming_for_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:44:00 by abartell          #+#    #+#             */
/*   Updated: 2022/10/19 15:03:16 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//goes through all args to get each of them trimmed
static char **args_trimming(char **args)
{
    int     i;
    char    **temp_args;
    char    *arg;

    i = 0;
    temp_args = matrix_duplicate(args);
    while (temp_args && temp_args[i])
    {
        arg = trim_argument(temp_args[i], 0, 0);
        free(temp_args[i]);
        temp_args[i] = arg;
        i++;
    }
    return (temp_args);
}

//counts the ' and " that do not need to be printed out
static int count_quotes(char const *arg, int squotes, int dquotes)
{
    int sum;
    int i;
    
    i = 0;
    sum = 0;
    
    while (arg && arg[i])
	{
		squotes = (squotes + (!dquotes && arg[i] == '\'')) % 2;
		dquotes = (dquotes + (!squotes && arg[i] == '\"')) % 2;
		if ((arg[i] == '\"' && !squotes) || (arg[i] == '\'' && !dquotes))
			sum++;
		i++;
	}
	if (squotes || dquotes)
		return (-1);
	return (sum);
}

//trimms a given argument, calls count_quotes to know what we do not need to malloc for
char    *trim_argument(char const *arg, int squotes, int dquotes)
{
    int     quotes_sum;
    int     i[2];
    char    *shortened;
    
    i[1] = -1;
    i[0] = 0;
    quotes_sum = count_quotes(arg, 0, 0);
    if (!arg || quotes_sum == -1)
        return(NULL);
    shortened = malloc(sizeof(char) * (ft_strlen(arg) - quotes_sum + 1));
    if (!shortened)
        return (NULL);
    while (arg[i[0]])
    {
        dquotes = (dquotes + (!squotes && arg[i[0]] == '\"')) % 2;
        squotes = (squotes + (!dquotes && arg[i[0]] == '\'')) % 2;
        if ((arg[i[0]] != '\"' || squotes) && (arg[i[0]] != '\'' || dquotes) && ++i[1] >= 0)
            shortened[i[1]] = arg[i[0]];
        i[0]++;
    }
    shortened[++i[1]] = '\0';
    return (shortened);
}
