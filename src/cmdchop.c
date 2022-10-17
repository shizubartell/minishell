/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdchop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:54:36 by abartell          #+#    #+#             */
/*   Updated: 2022/10/17 10:24:30 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../inc/minishell.h>

//needing one static function, called count_input, to iterate through the input
//from the terminal (string) to count the amount of input commands
//needing a second static function called fill_2darray which is used to fill 
//our matrix with the given input from the terminal to be used for 
//followed up processing of chopping the input up into different 
//builtins (cmd, pwd, arg, etc)
//one main function to use count_input and fill_2darray for splitting up
//the terminal input for future parsing

//counting the amount of input commands (string) into the terminal.
//this static function takes also care of handling single and double
//quotes so the terminal can properly handle the input
static int  count_input(const char *s, char *c, int av[2])
{
    int     i[2];

    i[0] = 0;
    i[1] = 0;
    while (s[av[0]] != '\0')
    {
        if (!ft_strchr(c, s[av[0]]))
        {
            av[1]++;
            while ((!ft_strchr(c, s[av[0]]) || i[0]) && s[av[0]] != '\0')
            {
                if (!i[1] && (s[av[0]] == '\"' || s[av[0]] == '\''))
                    i[1] = s[av[0]];
                i[0] = (i[0] + (s[av[0]] == i[1])) % 2;
                i[1] *= i[0] != 0;
                av[0]++; 
            }
            if (i[0])
                return (-1);
        }
        else
            av[0]++;
    }
    return (av[1]);
}

// filling our matrix with the input from count_input to be able to determine 
// the terminal input and the included commands from it, handling of 
// singlequoutes and doublequoutes included, chopping the input into 
// the different builtins
static char **fill_2darray(char **add, char const *s, char *set, int av[3])
{
    int     len;
    int     i[2];

    i[0] = 0;
    i[1] = 0;
    len = ft_strlen(s);
    while (s[av[0]])
    {
        while (ft_strchr(set, s[av[0]]) && s[av[0]] != '\0')
            av[0]++;
        av[1] = av[0];
        while ((!ft_strchr(set, s[av[0]]) || i[0] || i[1]) && s[av[0]])
        {
            i[0] = (i[0] + (!i[1] && s[av[0]] == '\'')) % 2;
            i[1] = (i[1] + (!i[0] && s[av[0] ]== '\"')) % 2;
            av[0]++;
        }
        if (av[1] >= len)
            add[av[2]++] = "\0";
        else
            add[av[2]++] = ft_substr(s, av[1], av[0] - av[1]);
    }
    return (add);
}

//using the static functions count_input and fill_2darray this function
//"chops" the commands into parts to give proper input from the terminal 
//to the remaining programm for further processing
char    **command_chop(char const *s, char *batch)
{
    char    **add;
    int     cword;
    int     i[3];
    int     count[2];

    i[0] = 0;
    i[1] = 0;
    i[2] = 0;
    count[0] = 0;
    count[1] = 0;
    if (!s)
        return (NULL);
    cword = count_input(s, batch, count);
    if (cword == -1)
        return (NULL);
    add = malloc((cword + 1) * sizeof(char *));
    if (add == NULL)
        return (NULL);
    add = fill_2darray(add, s, batch, i);
    add[cword] = NULL;
    return (add);
}