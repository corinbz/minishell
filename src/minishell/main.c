/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/02 12:17:50 by ccraciun         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */