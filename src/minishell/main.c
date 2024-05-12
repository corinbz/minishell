/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/12 11:13:32 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd*	execcmd(void)
{
	t_cmd *cmd;
	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0 , sizeof(*cmd));
	cmd->type = EXEC;
	return(t_cmd*)cmd;
}
//later we can put all parameters to the function(file, mode,fd, etc.)
t_cmd*	redircmd(void)
{
	t_redircmd	*cmd;
	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	// cmd->cmd = "command";
	cmd->file = "filename";
	cmd->efile = '\0';
	cmd->mode = 2;
	cmd->fd = 0;
	return (t_cmd*)cmd;
}

int main(int argc, char **argv)
{
	// static t_minishell	*m;

	// m = malloc(sizeof(t_minishell));
	printf("ac is %d and program name is %s\n",argc, argv[0] );
	t_cmd	*cmd = execcmd();
	t_redircmd	*redir_cmd = (t_redircmd*)redircmd();
	printf("t_cmd type is %d\n", cmd->type);
	printf("redircmd\ntype: %d\nfile: %s\n",redir_cmd->type, redir_cmd->file);
	// minishell_run(m);
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */