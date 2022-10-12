/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2darray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:10:30 by abartell          #+#    #+#             */
/*   Updated: 2022/10/12 15:25:26 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int matrixlength(char **array)
{
    int i;

    i = 0;
    while (array && array[i] != '\0')
        i++;
    return (i);
}

char    **addrowmatrix(char **input, char *str)
{
    char	**output;
    int		row;
	int		i;

	i = -1;
	output = NULL;
	if (!str)
		return (input);
	row = matrixlength(input);
	output = malloc(sizeof(char *) * (row + 2));
	output[row + 1] = NULL;
	if (!output)
		return (input);
	while (++i < row)
	{
		output[i] = ft_strdup(input[i]);
		if (!output[i])
		{
			free_matrix(&input);
			free_matrix(&output);
		}
	}
	output[i] = ft_strdup(str);
	free_matrix(&input);
	return (output);
}

int		matrix_to_fd(char **array, int line, int fd)
{
	int i;
	int adding;

	adding = 0;
	i = 0;
	while (array && array[i])
	{
		if (line)
			adding = adding + strnl_to_fd(array[i], fd);
		else
			adding = adding + str_to_fd(array[i], fd);
		i++;
	}
	return (adding);
}

int	str_to_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}

int	strnl_to_fd(char *s, int fd)
{
	if (s != NULL)
	{
		str_to_fd(s, fd);
		ft_putchar_fd('\n', fd);
		return ((int)ft_strlen(s) + 1);
	}
	return (0);
}