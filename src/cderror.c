/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cderror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:14:53 by abartell          #+#    #+#             */
/*   Updated: 2022/11/01 11:45:00 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//general command of "cd" like in bash
//setting the env value differently according to
//having to add a new row (cd) to our matrix or not
int cding(t_prompt *path)
{
    char	**str[2];
	char	*add;

	status = 0;
	str[0] = ((t_node *)path->cmds->content)->full_cmd;
	add = get_env_value("HOME", path->envp, 4);
	if (!add)
		add = ft_strdup("");
	str[1] = addrowmatrix(NULL, add);
	free(add);
	cdingerror(str);
	if (!status)
		path->envp = set_env_value("OLDPWD", str[1][1], path->envp, 6);
	add = getcwd(NULL, 0);
	if (!add)
		add = ft_strdup("");
	str[1] = addrowmatrix(str[1], add);
	free(add);
	path->envp = set_env_value("PWD", str[1][2], path->envp, 3);
	free_matrix(&str[1]);
	return(status);
}

//checks for errors and returns whether the
//first directory is an array or not
void	cdingerror(char **str[2])
{
	DIR		*directory;

	directory = NULL;
	if (str[0][1])
		directory = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		status = 1;
		ft_putstr_fd("minishell: Home not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		status = chdir(str[1][0]) == -1;
	if (str[0][1] && directory && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		errormsg(NODIR, str[0][1], 1);
	else if (str[0][1])
		errormsg(NOT_DIR, str[0][1], 1);
	if (str[0][1] && directory)
		closedir(directory);
}

//errormessages according to certain encounters like
//in bash
void	*errormsg(int type, char *var, int error)
{
	status = error;
	if (type == NODIR)
		ft_putstr_fd("minishell: No such file or directoy: ", 2);
	else if (type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	else if (type == NOPERM)
		ft_putstr_fd("minishell: Permission denied: ", 2);
	else if (type == DUPFAIL)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (type == FORKFAIL)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (type == NOCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	ft_putendl_fd(var, 2);
	return(NULL);
}