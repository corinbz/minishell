/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/21 12:01:30 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	minishell_run(t_minishell *m,char **envp, t_link_list *my_envp,
						t_exit_status *exit_sts)
{
	char	*input;
	t_cmd	*cmd;
	
	run_signals(1);
	struct termios saved_termios;
	struct termios raw_termios;
	while (1)
	{
		tcgetattr(STDIN_FILENO, &saved_termios);
		raw_termios = saved_termios;
		cfmakeraw(&raw_termios);
		input = readline("minishell: ");
		rl_on_new_line();
		// rl_redisplay();
		if (!input)
		{
			printf("no input found.. exiting\n");
			// rl_replace_line("", 0);
			// rl_redisplay();
			// run_signals(3);
			exit(0); //add cleanup
		}
		if (*input)
		{
			add_history(input);
			ft_lstadd_back(&m->input_history, ft_lstnew(input));
			input = expand_ret_value(input,exit_sts);
			printf("input: %s\n", input);
			expand_dollar_signs(input,my_envp);
			cmd = parse_cmd(input);
			// print_cmd_structure(cmd, 0);
			exit_sts->exit_status = exec_cmd(cmd,envp,my_envp, false);
			free(input);
			// free(cmd);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}

/*
 * main program loop that connects with other modules (input parsing, history etc)
 *
 * we have add_history for readline history
 * and we have linked list because we can't use history_list() from readline
 */