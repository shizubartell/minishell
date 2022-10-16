/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcmdchop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:20:44 by abartell          #+#    #+#             */
/*   Updated: 2022/10/16 17:32:58 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//additionally to cmdchop this part of the programm is also splitting substrings
//and handling the counting, iterating through it and 
//also the single or doublequotes it might encounter
//differently to cmdchop our count_words doesnt go through different
//argument values but only iterates through the count as long as the string
//and our string[i] dont hit the NULL Terminator.

static int	count_word(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**fill_2darray(char **aux, char *s, char *set, int av[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[av[0]] != '\0')
	{
		av[1] = av[0];
		if (!ft_strchr(set, s[av[0]]))
		{
			while ((!ft_strchr(set, s[av[0]]) || q[0] || q[1]) && s[av[0]])
			{
				q[0] = (q[0] + (!q[1] && s[av[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[av[0]] == '\"')) % 2;
				av[0]++;
			}
		}
		else
			av[0]++;
		aux[av[2]++] = ft_substr(s, av[1], av[0] - av[1]);
	}
	return (aux);
}

//additionally to cmdchop this part of the programm is also splitting substrings
//and handling the counting, iterating through it and 
//also the single or doublequotes it might encounter
//differently to cmdchop our count_words doesnt go through different
//argument values but only iterates through the count as long as the string
//and our string[i] dont hit the NULL Terminator.
char	**subcmd_chop(char const *s, char *set)
{
	char	**add;
	int		cword;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	cword = count_word((char *)s, set, 0);
	if (cword == -1)
		return (NULL);
	add = malloc((cword + 1) * sizeof(char *));
	if (add == NULL)
		return (NULL);
	add = fill_2darray(add, (char *)s, set, i);
	add[cword] = NULL;
	return (add);
}
