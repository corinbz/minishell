/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/21 19:26:49 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_run(t_minishell *m,char **envp, t_link_list *my_envp)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
		input = readline("minishell: ");
		rl_on_new_line();
		if (!input)
		{
			printf("exit\n");
			exit(0); //add cleanup
		}
		if (*input)
		{
			add_history(input);
			ft_lstadd_back(&m->input_history, ft_lstnew(input));
			cmd = parse_cmd(input);
			exec_cmd(cmd,envp,my_envp, false);
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