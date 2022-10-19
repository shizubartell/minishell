/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2darray2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:26:14 by abartell          #+#    #+#             */
/*   Updated: 2022/10/18 11:03:50 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// duplicating our matrix via usage of stringduplicate
// freeing the output

char    **matrix_duplicate(char **array)
{
    char    **output;
    int		row;
	int		i;

	row = matrixlength(array);
	output = malloc(sizeof(char *) * (row + 1));
	if (!output)
		return (NULL);
	i = 0;
	while(array[i])
	{
		output[i] = ft_strdup(array[i]);
		if (!output[i])
		{
			free_matrix(&output);
			return (NULL);
		}
		i++;
	}
	output[i] = NULL;
	return (output);
}

//freeing the matrix 

void	free_matrix(char ***array)
{
	int	i;

	i = 0;
	while (array && array[0] && array[0][i])
	{
		free(array[0][i]);
		i++;
	}
	if (array)
	{
		free(array[0]);
		*array = NULL;
	}
}

// using calloc to allocate memory for our 2darray
// replacing a line in the matrix/2darray (not necessarily end or beginning
// of the array) if the arrangement changes
// using strdup to duplicate the string according to the changes
// freeing our char high at the end to then return the pointer

//replacing nth-line with another matrix
char	**replace_matrixline(char ***high, char **low, int c)
{
	int i[3];
	char **add;

	add = ft_calloc(matrixlength(*high) + matrixlength(low), sizeof(char *));
	if (!high || !*high || c < 0 || c >= matrixlength(*high))
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (add && high[0][++i[0]])
	{
		if (i[0] != c)
			add[++i[2]] = ft_strdup(high[0][i[0]]);
		else
		{
			while (low && low[++i[1]])
				add[++i[2]] = ft_strdup(low[i[1]]);
		}
	}	
	free_matrix(high);
	*high = add;
	return (*high);
}
