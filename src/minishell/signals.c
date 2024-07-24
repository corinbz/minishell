/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:35:17 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/21 12:26:28 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		// printf("exit\n");
		exit(0);
	}
}

void	restore_prompt(int sig)
{
	g_signal = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_signal = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	g_signal = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}