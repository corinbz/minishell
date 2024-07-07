/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/07 13:36:25 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

int main(int argc, char **argv, char **envp)
{
	t_link_list	*my_envp;
	t_minishell	*input;
	t_exit_status	*exit_sts;

	if (argc != 1 || argv[1])
	{
		ft_panic("This program does not accept arguments\n");
	}
	exit_sts = ft_calloc(1, sizeof(*exit_sts));
	if (!exit_sts)
		return (1);
	my_envp = create_my_envp(envp);
	input = ft_calloc(1, sizeof(t_minishell*));
	minishell_run(input,envp,my_envp);
	return (EXIT_SUCCESS);
}
