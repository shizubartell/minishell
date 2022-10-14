/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abartell <abartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:38:27 by abartell          #+#    #+#             */
/*   Updated: 2022/10/14 13:49:50 by abartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// handling our signals for the terminal input
// ioctl is a direct command that makes it possible to
// send and handle terminal input and is accessing the
// file descriptor and we are using TIOCSTI to directly
// inject input into the terminal
// TIOC from "Terminal IOCtl" and STI from "Send Terminal Input".
// its helping our subshell to be able to work as a shell
// #include <sys/ioctl.h> for usage of TIOCSTI which has the standard
// C value of 0x5412
// status = 128 + SIGINT => simplified representation of exit status after
// the last input died of SIGINT

void    handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        status = 130;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        rl_replace_line("", 0);
        rl_on_new_line();
    }
}