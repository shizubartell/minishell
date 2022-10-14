/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandtrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:54:36 by abartell          #+#    #+#             */
/*   Updated: 2022/10/14 11:11:08 by abartell         ###   ########.fr       */
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

static int  count_input(const char *s, char *c, int av[2])
{
    int     i[2];

    i[0] = 0;
    i[1] = 0;
}

static char **fill_2darray(char **add, char const *s, char *set, int i[3])
{
    
}