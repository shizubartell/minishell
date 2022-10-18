/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:04:48 by abartell          #+#    #+#             */
/*   Updated: 2022/10/18 10:25:25 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int string_chars(const char *s, char *batch)
{
    int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(batch, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

//expands our ~ to our home directory in a string
//if it is not in quotes
char	*pathexpander(char *str, int i, int qs[2], char *vars)
{
	char	*path;
	char	*add;

	qs[0] = 0;
	qs[1] = 0;
	while (str && str[++i])
	{
		qs[0] = (qs[0] + (!qs[1] && str[i] == '\'')) % 2;
		qs[1] = (qs[1] + (!qs[0] && str[i] == '\"')) % 2;
		if (!qs[0] && !qs[1] && str [i] == '~' && \
			(i == 0 || str [i - 1] != '$'))
		{
			add = ft_substr(str, 0, i);
			path = ft_strjoin(add, vars);
			free(add);
			add = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, add);
			free(add);
			free(path);
			return (pathexpander(str, i + ft_strlen(vars) - 1, qs, vars));
		}
	}
	free (vars);
	return (str);
}

//adding the path of the substring with variable inputs from
//pipes to quotes to slashes and adding it to our home path
//to be able to change directories
//setting pid to be able to pull the process ID and getting envp
//information via our structure
static char	*vars_substring(char *str, int i, t_prompt *get)
{
	char	*add;
	char	*path;
	char	*vars;
	int		pos;

	pos = string_chars(&str[i], "|\"\'$?<> ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	add = ft_substr(str, 0, i - 1);
	vars = get_env_value(&str[i], get->envp, \
			string_chars(&str[i], "\"\'$|<> "));
	if (!vars && str[i] == '$')
		vars = ft_itoa(get->pid);
	else if (!vars && str[i] == '?')
		vars = ft_itoa(status);
	path = ft_strjoin(add, vars);
	free(add);
	add = ft_strjoin(path, &str[i + pos]);
	free(str);
	free(vars);
	free(path);
	return (add);
}

//expands enviroment variables in a string if not in quotes
char	*expanding_vars(char *str, int i, int qs[2], t_prompt *get)
{
	qs[0] = 0;
	qs[1] = 0;

	while (str && str[++i])
	{
		qs[0] = (qs[0] + (!qs[1] && str[i] == '\'')) % 2;
		qs[1] = (qs[1] + (!qs[0] && str[i] == '\"')) % 2;
		if (!qs[0] && str[i] == '$' && str[i + 1] && \
			((string_chars(&str[i + 1], "/~%^{}:; ") && !qs[1]) || \
			(string_chars(&str[i +1], "/~%{}:;\"") && qs[1])))
			return (expanding_vars(vars_substring(str, ++i, get), -1, \
				qs, get));
	}
	return (str);
}
