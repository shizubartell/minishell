/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:34:09 by iczarnie          #+#    #+#             */
/*   Updated: 2022/11/01 14:06:41 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//looks for a variable (+place of "=") in envp
static int	finding_env_var(char *argv, char **envp, int array[2])
{
	int	pos;

	array[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[array[1]])
	{
		if (!ft_strncmp(envp[array[1]], argv, pos + 1))
			return (1);
		array[1]++;
	}
	return (0);
}

//exports an environmental variable, the input format is X=Y, has 2 
//conditions = there was no
//variable with that name - adds it, if there was one - it changes the value
int	export(t_prompt *prompt)
{
	int		arr[2];
	int		pos;
	char	**argv;

	argv = ((t_node *)prompt->cmds->content)->full_cmd;
	if (matrixlength(argv) >= 2)
	{
		arr[0] = 1;
		while (argv[arr[0]])
		{
			pos = finding_env_var(argv[arr[0]], prompt->envp, arr);
			if (pos == 1)
			{
				free(prompt->envp[arr[1]]);
				prompt->envp[arr[1]] = ft_strdup(argv[arr[0]]);
			}
			else if (!pos)
				prompt->envp = addrowmatrix(prompt->envp, argv[arr[0]]);
			arr[0]++;
		}
	}
	return (0);
}

//unsets an environmental variable, checks if there is "=", 
//if not then adds it so finding_env_var will work properly
int	unset(t_prompt *prompt)
{
	char	**argv;
	char	*temp;
	int		arr[2];

	arr[0] = 0;
	argv = ((t_node *)prompt->cmds->content)->full_cmd;
	if (matrixlength(argv) >= 2)
	{
		while (argv[++arr[0]])
		{
			if (argv[arr[0]][ft_strlen(argv[arr[0]]) - 1] != '=')
			{
				temp = ft_strjoin(argv[arr[0]], "=");
				free(argv[arr[0]]);
				argv[arr[0]] = temp;
			}
			if (finding_env_var(argv[arr[0]], prompt->envp, arr))
				replace_matrixline(&prompt->envp, NULL, arr[1]);
		}
	}
	return (0);
}
