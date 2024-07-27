/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:35:17 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/27 17:25:07 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_exit_sts(t_link_list *my_envp)
{
	int	res;
	t_link_list	*curr;
	
	curr = my_envp;
	res = 0;
	while(curr)
	{
		if(ft_strncmp(curr->param, "?=", 2) == 0)
		{
			res = ft_atoi(curr->param + 2);
			break;
		}
		curr = curr->next;
	}
	return(res);
}

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