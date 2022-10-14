/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:06:08 by abartell          #+#    #+#             */
/*   Updated: 2022/10/14 15:52:03 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// generates prompt message - so username + directory before (in pink:D) $ (afer that basic colour) 
static char *generate_prompt_message(void)
{
	char *temp[2];
	
	temp[0] = getcwd(NULL, 0);
	temp[1] = ft_strjoin("\001\033[1;95m\002minishell ", temp[0]);
	free(temp[0]);
	temp[0] = ft_strjoin(temp[1], "$ \001\033[0;39m\002");
	free(temp[1]);
	return(temp[0]);	
}

static void	*check_args(char *out, t_prompt *p)
{
	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
}	

int main(int argc, char **argv, char **envp)
{
    char       *str;
    char        *out;
    t_prompt initial;

    initial = initialise_prompt(argv, envp);
    while (argv && argc)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = generate_prompt_message();
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		if (!check_args(out, &initial))
			break;
	}
	exit(0);
}
