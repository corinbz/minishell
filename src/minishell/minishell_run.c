/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:10:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/11 19:26:25 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_run(t_minishell *m)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (!input)
		{
			printf("exit\n");
			exit(0); //add cleanup
		}
		if (*input)
		{
			add_history(input);
			ft_lstadd_back(&m->input_history, ft_lstnew(input));
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