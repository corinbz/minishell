/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/31 19:07:45 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// void	minishell_run(char **envp, t_link_list *my_envp,
// 			t_exit_status *exit_sts)
// {
// 	char			*input;
// 	t_cmd			*cmd;
// 	struct termios	saved_termios;
// 	struct termios	raw_termios;

// 	run_signals(1);
// 	while (1)
// 	{
// 		tcgetattr(STDIN_FILENO, &saved_termios);
// 		raw_termios = saved_termios;
// 		cfmakeraw(&raw_termios);
// 		input = readline("minishell: ");
// 		rl_on_new_line();
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			if (g_signal != 0)
// 				exit(g_signal);
// 			exit(exit_sts->exit_status);
// 		}
// 		if (*input)
// 		{
// 			add_exit_status_to_envp(&my_envp, exit_sts);
// 			expand_env_vars_and_quotes(&input, my_envp, exit_sts);
// 			cmd = parse_cmd(input);
// 			if (!is_heredoc_cmd(cmd))
// 				add_history(input);
// 			exit_sts->exit_status = exec_cmd(cmd, envp, my_envp, false);
// 			g_signal = 0;
// 			free(input);
// 			free_full_cmd(cmd);
// 		}
// 		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
// 	}
// }

#include "minishell.h"


void	minishell_run(char **envp, t_link_list *my_envp,
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
