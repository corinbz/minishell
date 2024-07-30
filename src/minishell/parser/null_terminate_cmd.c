/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_terminate_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:41:12 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/27 16:37:20 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	null_terminate_cmd_continue(t_cmd *cmd)
{
	t_redir_cmd	*temp_redir_cmd;
	t_pipe_cmd	*temp_pipe_cmd;

	if (cmd->type == REDIR)
	{
		temp_redir_cmd = (t_redir_cmd *)cmd;
		null_terminate_cmd(temp_redir_cmd->sub_cmd);
		*(temp_redir_cmd->token_end_pos) = '\0';
	}
	if (cmd->type == PIPE)
	{
		temp_pipe_cmd = (t_pipe_cmd *)cmd;
		null_terminate_cmd(temp_pipe_cmd->left);
		null_terminate_cmd(temp_pipe_cmd->right);
	}
}

void	null_terminate_cmd(t_cmd *cmd)
{
	int			i;
	t_exec_cmd	*temp_exec_cmd;

	if (cmd->type == EXEC)
	{
		i = 0;
		temp_exec_cmd = (t_exec_cmd *)cmd;
		while (i < MAX_ARGUMENTS && temp_exec_cmd->arg_end[i])
			i++;
		if (i < MAX_ARGUMENTS)
			temp_exec_cmd->arg_end[i] = NULL;
	}
	if (cmd->type == REDIR || cmd->type == PIPE)
		null_terminate_cmd_continue(cmd);
}
