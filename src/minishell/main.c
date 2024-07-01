/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/01 06:50:48 by erybolov         ###   ########.fr       */
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
	if (argc != 1 || argv[1])
	{
		ft_panic("This program does not accept arguments\n");
		exit(0);
	}
	t_link_list *my_envp = create_my_envp(envp); //	ft_env(my_envp);
	char *input = readline("minishell: ");
	expand_env_vars_and_quotes(&input, my_envp);

	t_cmd	*output = parse_cmd(input);
	return (EXIT_SUCCESS);
}
