/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/16 18:52:23 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv)
{
	static char	buff[100];
	printf("ac is %d and program name is %s\n",argc, argv[0] );
	t_cmd	*cmd = execcmd();
	// t_redircmd	*redir_cmd = (t_redircmd*)redircmd();
	t_cmd	*redir_cmd = (t_cmd*)redircmd();
	printf("t_cmd type is %d\n", cmd->type);
	printf("redircmd\ntype: %d\nfile: s\n",redir_cmd->type);
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */