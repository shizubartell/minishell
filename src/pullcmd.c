/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pullcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:02:43 by abartell          #+#    #+#             */
/*   Updated: 2022/11/01 12:41:40 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*cmd_finder(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

//checking if the part of the path is a builtin
//from our list
static DIR	*cmd_checker(t_prompt *prompt, t_list *cmd, char ***s, char *path)
{
	t_node	*node;
	DIR		*dir;

	dir = NULL;
	node = cmd->content;
	if (node && node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node && node->full_cmd && ft_strchr(*node->full_cmd, '/') && !dir)
	{
		*s = ft_split(*node->full_cmd, '/');
		node->full_path = ft_strdup(*node->full_cmd);
		free(node->full_cmd[0]);
		node->full_cmd[0] = ft_strdup(s[0][matrixlength(*s) - 1]);
	}
	else if (!builtins(node) && node && node->full_cmd && !dir)
	{
		path = get_env_value("PATH", prompt->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		node->full_path = cmd_finder(*s, *node->full_cmd, node->full_path);
		if (!node->full_path || !node->full_cmd[0] || !node->full_cmd[0][0])
			errormsg(NOCMD, *n->full_cmd, 127);
	}
	return (dir);
}

//checks if a cmd is in the PATH variable and pulls
//its full path
void	get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_node	*node;
	DIR		*dir;

	node = cmd->content;
	dir = cmd_checker(prompt, cmd, &s, path);
	if (!builtins(node) && node && node->full_cmd && dir)
		errormsg(IS_DIR, *n->full_cmd, 126);
	else if (!builtins(node) && node && node->full_path && \
		access(node->full_path, F_OK) == -1)
		errormsg(NODIR, node->full_path, 127);
	else if (!builtins(node) && node && node->full_path && \
		access(node->full_path, X_OK) == -1)
		errormsg(NOPERM, node->full_path, 126);
	if (dir)
		closedir(dir);
	free_matrix(&s);
}

//executing a non builtin command followed
//on our list
void	*ex_nocmd(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];

	get_cmd(prompt, cmd, NULL, NULL);
	if (!fork_checker(prompt, cmd, fd))
		return (NULL);
	if (pipe(fd) == -1)
		return (errormsg(PIPERR, NULL, 1));
	close(fd[WRITE_END]);
	if (cmd->next && !((t_node *)cmd->next->content)->inputfile)
		((t_node *)cmd->next->content)->inputfile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_node *)cmd->content)->outputfile > 2)
		close(((t_node *)cmd->content)->outputfile);
	if (((t_node *)cmd->content)->inputfile > 2)
		close(((t_node *)cmd->content)->inputfile);
	return (NULL);
}