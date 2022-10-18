/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:54:41 by abartell          #+#    #+#             */
/*   Updated: 2022/10/18 10:44:59 by abartell         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>

//*********************************************************//
//**                GLOBAL VARIABLE                     **//

int				status;     

//*********************************************************//
//**                STRUCTURES                          **//

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

//*********************************************************//
//**                MAIN.C                              **//

int				main(int argc, char **argv, char **envp);

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

//*********************************************************//
//**                SIGNAL.C                            **//

void			handle_sigint(int sig);

//*********************************************************//
//**                INITIALISE_PROMPT.C                  **//

t_prompt        initialise_prompt(char **argv, char **envp);
char            **set_env_value(char *var, char *value, char **envp, int n);
char            *get_env_value(char *var, char **envp, int n);
int				strchr_int(const char *s, int c);

//*********************************************************//
//**                EXPANDING.C                         **//

char			*pathexpander(char *str, int i, int qs[2], char *vars);
char			*expanding_vars(char *str, int i, int qs[2], t_prompt *get);

//*********************************************************//
//**                TRIMMING_FOR_NODES.C                **//

char			*trim_argument(char const *arg, int squotes, int dquotes);

#endif