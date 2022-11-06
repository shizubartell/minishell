/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:18:41 by abartell          #+#    #+#             */
/*   Updated: 2022/11/06 17:43:43 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	*child_redirection(t_list *cmd, int fd[2])
{
	t_node	*node;

	node = cmd->content;
	if (node->inputfile != STDIN_FILENO)
	{
		if (dup2(node->inputfile, STDIN_FILENO) == -1)
			return (errormsg(DUPFAIL, NULL, 1));
		close(node->inputfile);
	}
	if (node->outputfile != STDOUT_FILENO)
	{
		if (dup2(node->outputfile, STDOUT_FILENO) == -1)
			return (errormsg(DUPFAIL, NULL, 1));
		close(node->outputfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (errormsg(DUPFAIL, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

//executing commands inside the child process
//SIG_IGN to ignore the signal in the process
//execve is coming from the unistd.h lib and is used to replace 
//the whole currently running process in the child
void	child_builtins(t_prompt *prompt, t_node *n, int i, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!builtins(n) && n->full_cmd)
		execve(n->full_path, n->full_cmd, prompt->envp);
	else if (builtins(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", i) && i == 3)
	{
		matrix_to_fd(prompt->envp, 1, 1);
		g_status = 0;
	}
	else if (builtins(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "echo", i) && i == 4)
		g_status = echopath(cmd);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", i) \
		&& i == 3)
		g_status = pwdpath();
}

void	*child_proc(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_node	*n;
	int		i;

	n = cmd->content;
	i = 0;
	if (n->full_cmd)
		i = ft_strlen(*n->full_cmd);
	child_redirection(cmd, fd);
	close(fd[READ_END]);
	child_builtins(prompt, n, i, cmd);
	ft_lstclear(&prompt->cmds, free_node);
	exit(g_status);
}

void	fork_execution(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		errormsg(FORKFAIL, NULL, 1);
	}
	else if (!pid)
		child_proc(prompt, cmd, fd);
}

//checks if the conditions to
//perform a fork are met or not
void	*fork_checker(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_node	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n->inputfile == -1 || n->outputfile == -1)
		return (NULL);
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if ((n->full_path && access(n->full_path, X_OK) == 0) || builtins(n))
		fork_execution(prompt, cmd, fd);
	else if (!builtins(n) && ((n->full_path && \
		!access(n->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!builtins(n) && n->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
