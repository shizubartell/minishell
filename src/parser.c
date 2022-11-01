/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:51:39 by abartell          #+#    #+#             */
/*   Updated: 2022/11/01 15:04:07 by abartell         ###   ########.fr       */
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
