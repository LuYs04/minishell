/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:43:24 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 18:16:11 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_event_loop(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_next_line);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_next_line(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exitcode = 1;
}

void	ft_sigquit(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
	g_exitcode = 131;
}

void	ft_sigline(int sig)
{
	(void)sig;
	printf("\n");
	g_exitcode = 130;
}

void	ctrl_d_exit(void)
{
	printf("exit\n");
	g_exitcode = 0;
	exit(0);
}
