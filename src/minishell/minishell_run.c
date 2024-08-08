/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/06 20:18:45 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_run(char **envp, t_link_list **my_envp,
	t_exit_status *exit_sts)
{
	struct termios	saved_termios;
	struct termios	raw_termios;

	run_signals(1);
	while (1)
	{
		initialize_terminal(&saved_termios, &raw_termios);
		read_and_process_input(envp, my_envp, exit_sts);
		reset_terminal(&saved_termios);
	}
}
