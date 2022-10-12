/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:54:41 by abartell          #+#    #+#             */
/*   Updated: 2022/10/12 17:10:29 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//*********************************************************//
//**                INCLUDES                            **//

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>


//*********************************************************//
//**                STRUCTURES                          **//

typedef struct s_env
{
    char        **input;
    char		**output;
}   t_env;

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

//*********************************************************//
//**                MAIN.C                              **//

int startup(char **path);

//*********************************************************//
//**                2DARRAY.C                           **//

int             matrixlength(char **array);
char            **addrowmatrix(char **input, char *str);
int             matrix_to_fd(char **array, int line, int fd);
int             str_to_fd(char *s, int fd);
int             strnl_to_fd(char *s, int fd);

//*********************************************************//
//**                2DARRAY2.C                          **//

char            **matrix_duplicate(char **array);
void            free_matrix(char ***array);
char            **replace_matrixline(char ***high, char **low, int c);

#endif