/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/20 13:45:39 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	minishell_run(t_minishell *m,char **envp, t_link_list *my_envp)
{
	char	*input;
	t_cmd	*cmd;

	// run_signals(2);
	while (1)
	{
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
			expand_dollar_signs(input,my_envp);
			cmd = parse_cmd(input);
			print_cmd_structure(cmd, 0);
			exec_cmd(cmd,envp,my_envp, false);
			free(input);
			// free(cmd);
			//parse & process input functions
		}
	}
}

/*
 * main program loop that connects with other modules (input parsing, history etc)
 *
 * we have add_history for readline history
 * and we have linked list because we can't use history_list() from readline
 */