/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/31 20:03:00 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_link_list		*my_envp;
	t_exit_status	*exit_sts;

	if (argc != 1 || argv[1])
		ft_panic("This program does not accept arguments\n");
	exit_sts = ft_calloc(1, sizeof(*exit_sts));
	if (!exit_sts)
		return (1);
	my_envp = create_my_envp(envp);
	if (!my_envp)
	{
		printf("Failed to create environment list\n");
		return (1);
	}
	minishell_run(envp, my_envp, exit_sts);
	free_envp(&my_envp);
	free(exit_sts);
	return (EXIT_SUCCESS);
}
