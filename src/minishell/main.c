/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 11:37:39 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *test1 = "echo hello";

int main(int argc, char **argv, char **envp)
{
	// static t_minishell	*m;

	// m = malloc(sizeof(t_minishell));
	printf("ac is %d and program name is %s\n",argc, argv[0] );
	t_cmd	*cmd = execcmd();
	// t_redircmd	*redir_cmd = (t_redircmd*)redircmd();
	// t_cmd	*redir_cmd = (t_cmd*)redircmd();
	printf("t_cmd type is %d\n", cmd->type);
	// printf("redircmd\ntype: %d\nfile: s\n",redir_cmd->type);
	// minishell_run(m);
	ft_pwd(envp);
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */