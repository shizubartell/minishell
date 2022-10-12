/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:06:08 by abartell          #+#    #+#             */
/*   Updated: 2022/10/11 13:01:36 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int startup(char **path)
{
   char *line;
   
   line = readline("\033[0;94mMinishell v1.0 $> \e[0m");
   while (line)
   {
        if ()
        {
            add_history(line);
        }
        line = readline("\033[0;94mMinishell v1.0 $> \e[0m");
   }
   return (0);
}
q