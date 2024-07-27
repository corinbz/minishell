/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/27 15:20:30 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_run(char **envp, t_link_list *my_envp,
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
			printf("exit\n");
			// rl_replace_line("", 0);
			// rl_redisplay();
			// run_signals(3);
			exit(0); //add cleanup
		}
		if (*input)
		{
			add_exit_status_to_envp(&my_envp, exit_sts);
			expand_env_vars_and_quotes(&input, my_envp, exit_sts);
			cmd = parse_cmd(input);
			if (!is_heredoc_cmd(cmd))
				add_history(input);
			printf("here\n");
//			 print_cmd_structure(cmd, 0);
			exit_sts->exit_status = exec_cmd(cmd,envp,my_envp, false);
			free(input);
//			free_full_cmd(cmd);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}
