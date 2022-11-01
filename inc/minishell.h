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
// # include <readline/readline.h>
// # include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "/Users/abartell/goinfre/.brew/Cellar/readline/8.2.1/include/readline/readline.h"
# include "/Users/abartell/goinfre/.brew/Cellar/readline/8.2.1/include/readline/history.h"

# define READ_END 0
# define WRITE_END 1

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

typedef struct s_node
{
	int		inputfile;
	int		outputfile;
    char	**full_cmd;
	char	*full_path;
}			t_node;

enum	error_msg
{
	NODIR = 1,
	NOT_DIR = 2,
	NOPERM = 3,
	DUPFAIL = 4,
	FORKFAIL = 5,
	NOCMD = 6,
	IS_DIR = 7,
	PIPERR = 9,
	PIPENDERR = 10
};

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

t_prompt        initialise_prompt(char **envp);
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
char			**args_trimming(char **args);

//*********************************************************//
//**                NODE_HELPER.C                       **//

t_node			*initialise_node(void);
t_list			*stop_fill(t_list *cmds, char **args, char **temp);
void			free_node(void *content);
t_list			*fill_nodes(char **args, int i);

//*********************************************************//
//**                PWDECHOEXIT.C                       **//

int				exitpath(t_list *cmd, int *ex);
int				pwdpath(void);
int				echopath(t_list *cmd);

//*********************************************************//
//**                CDERROR.C                           **//

int				cding(t_prompt *path);
void			cdingerror(char **str[2]);
void			*errormsg(int type, char *var, int error);

//*********************************************************//
//**                REDIRECTIONS.C                      **//

void			error_in_redirections(int *i, int file_descriptor);
t_node			*get_outfile1(t_node *node, char **args, int *i);
t_node			*get_outfile2(t_node *node, char **args, int *i);
t_node			*get_infile1(t_node *node, char **args, int *i);

//*********************************************************//
//**                EXECUTION.C                         **//

void			child_builtins(t_prompt *prompt, t_node *n, t_list *cmd);
void			*child_proc(t_prompt *s_prompt, t_list *cmd, int fd[2]);
void			fork_execution(t_prompt *prompt, t_list *cmd, int fd[2]);
void			*fork_checker(t_prompt *prompt, t_list *cmd, int fd[2]);

//*********************************************************//
//**                BUILTINS.C                          **//

int				builtins(t_node *node);

//*********************************************************//
//**                HEREDOC.C                           **//

t_node			*get_infile2(t_node *node, char **args, int *i);

//*********************************************************//
//**                PULLCMD.C                           **//

void			get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path);
void			*ex_nocmd(t_prompt *prompt, t_list *cmd);

//*********************************************************//
//**                PULLCMD.C                           **//

//*********************************************************//
//**                EXPORTUNSET.C                       **//

int				export(t_prompt *prompt);
int				unset(t_prompt *prompt);

#endif