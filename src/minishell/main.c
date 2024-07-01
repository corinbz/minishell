/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/01 13:38:33 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int free_cmd(t_cmd *cmd)
// {
// 	t_exec_cmd *cmde;

// 	if(cmd->type == EXEC)
// 	{
// 		cmde = (t_exec_cmd*)cmd;
// 		ft_free_2d(cmde->arg_start);
// 	}
// }
int main(int argc, char **argv, char **envp)
{
	t_link_list	*my_envp;
	t_minishell	*input;

	if (argc != 1 || argv[1])
	{
		ft_panic("This program does not accept arguments\n");
		exit(0);
	}
	my_envp = create_my_envp(envp);
	input = ft_calloc(1, sizeof(t_minishell*));
	minishell_run(input,envp,my_envp);
	return (EXIT_SUCCESS);
}
