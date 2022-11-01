/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwdechoexit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:12:05 by abartell          #+#    #+#             */
/*   Updated: 2022/11/01 11:10:07 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  countchar(char *s, char c)
{
    int counter;

    counter = 0;
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == c)
            counter++;
        s++;
    }
    return (counter);
}

static int	string_isonlynum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (1);
}

int	exitpath(t_list *cmd, int *ex)
{
	t_node	*node;
	long	status[2];

	status[0] = 0;
	node = cmd->content;
	*ex = !cmd->next;
	if (*ex)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	if (node->full_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (255);
	}
	else if (string_isonlynum(node->full_cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	return (status[0]);
}

int pwdpath(void)
{
    char    *buffer;
    
    buffer = getcwd(NULL, 0);
    ft_putendl_fd(buffer, 1);
    free(buffer);
    return (0);
}

int echopath(t_list *cmd)
{
    t_node  *node;
    int     nl;
    int     i[2];
    char    **av;

    node = cmd->content;
    nl = 1;
    i[0] = 0;
    i[1] = 0;
    av = node->full_cmd;

    while (av && av[++i[0]])
    {
        if (!i[1] && !ft_strncmp(av[i[0]], "-n", 2) && \
            (countchar(av[i[0]], 'n') == \
            (int)(ft_strlen(av[i[0]]) - 1)))
            nl = 0;
        else
        {
            i[1] = 1;
            ft_putstr_fd(av[i[0]], 1);
            if (av[i[0] + 1])
                ft_putchar_fd(' ', 1);
        }
    }
    return (write(1, "\n", nl) == 2);
}