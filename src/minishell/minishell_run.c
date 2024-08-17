/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/17 10:20:20 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_run(char **envp, t_link_list **my_envp,
	t_exit_status *exit_sts)
{
	struct termios	saved_termios;
	struct termios	raw_termios;

	while (1)
	{
		run_signals(1);
		initialize_terminal(&saved_termios, &raw_termios);
		read_and_process_input(envp, my_envp, exit_sts);
		reset_terminal(&saved_termios);
	}
}
