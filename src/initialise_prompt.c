/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:49:37 by iczarnie          #+#    #+#             */
/*   Updated: 2022/10/14 10:43:59 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//looks for the value in the envp (like what SHLVL we are at or if PATH has values)
char *get_env_value(char *var, char **envp, int n)
{
    int i;

    i = 0;
    if (n < 0)
        n = ft_strlen(var);
    while (!ft_strchr(var, '=') && envp && envp[i])
    {
        if(!ft_strncmp(envp[i], var, n))
            return(ft_substr(envp[i], n + 1, ft_strlen(envp[i])));
        i++;
    }
    return (NULL);
}

//sets a value in envp = just the value if that thing was in envp before, or the whole line 
//if there was nothing like that before
char **set_env_value(char *var, char *value, char **envp, int n)
{
    int     i[2];
    char    *temp[2];
    
    if (n < 0)
        ft_strlen(var);
    i[0] = 0;
    temp[0] = ft_strjoin(var, "=");
    temp[1] = ft_strjoin(temp[0], value);
    free(temp[0]);
    while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = strchr_int(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			temp[0] = envp[i[0]];
			envp[i[0]] = temp[1];
			free(temp[0]);
			return (envp);
		}
        i[0]++;
	}
    envp = addrowmatrix(envp, temp[1]);
    free(temp[1]);
    return (envp);
}

//finds and sets if there are none PWD, PATH and SHLVL in our envp
static t_prompt initialise_values(t_prompt prompt, char **argv)
{
    char        *str;
    char        *num;
    
    str = getcwd(NULL, 0);
    prompt.envp = set_env_value("PWD", str, prompt.envp, 3);
    free (str);
    str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	free(str);
    str = get_env_value("SHLVL", prompt.envp, 5);
    if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
    free(str);
    prompt.envp = set_env_value("SHLVL", num, prompt.envp, 5);
	free(num);
    return(prompt);
}

//returns first prompt enviromemnt, with a copy of **envp
//calls initialisation of values
t_prompt initialise_prompt(char **argv, char **envp)
{
    t_prompt    prompt;

    prompt.cmds = NULL;
    prompt.envp = matrix_duplicate(envp);
    prompt = initialise_values(prompt, argv);
    return(prompt);
}

//compared to our strchr this functions looks for a
//specific character inside a given string and returns
//that characters index
int strchr_int(const char *s, int c)
{
    unsigned int 	c;
    int				i;

	i = 0;
	c = (unsigned char)c;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}