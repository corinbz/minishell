/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/08 16:48:09 by ccraciun         ###   ########.fr       */
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
	// char	input[100] = "<";
	// t_cmd 	*output = parse_cmd(input);
	// exec_cmd(output, envp);
	// char *eof = "eof";
	// t_heredoc	*heredoc;
	// heredoc = ft_calloc(1, sizeof(*heredoc));
	// int status = ft_heredoc(heredoc, envp);
	// printf("%d\n", status);
	// free(heredoc);
	t_link_list *my_envp = create_my_envp(envp);
	// ft_export(NULL, my_envp);
	// ft_unset("PWD", &my_envp);
	ft_env(my_envp);
	// free_envp(&my_envp);
	// create_builtin_lst();
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */