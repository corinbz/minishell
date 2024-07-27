/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:48:05 by corin             #+#    #+#             */
/*   Updated: 2024/07/27 15:18:39 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//not done yet
void free_full_cmd(t_cmd *cmd)
{
	t_exec_cmd		*exec_cmd;
	t_heredoc_cmd	*heredoc_cmd;
	t_pipe_cmd		*pipe_cmd;
	t_redir_cmd		*redir_cmd;

	if (cmd->type == PIPE)
	{
		pipe_cmd = (t_pipe_cmd *)cmd;
		free_full_cmd((t_cmd *) pipe_cmd->left);
		free_full_cmd((t_cmd *) pipe_cmd->right);
		free(pipe_cmd);
	}
	else if (cmd->type == HEREDOC)
	{
		heredoc_cmd = (t_heredoc_cmd *)cmd;
		free_full_cmd((t_cmd *) heredoc_cmd->sub_cmd);
		free(heredoc_cmd);
		// ft_free_2d(exec_cmd->arg_start);
		// ft_free_2d(exec_cmd->arg_end);
	}
	else if (cmd->type == REDIR)
	{
		redir_cmd = (t_redir_cmd *)cmd;
		free_full_cmd((t_cmd *) redir_cmd->sub_cmd);
		free(redir_cmd);
		// ft_free_2d(exec_cmd->arg_start);
		// ft_free_2d(exec_cmd->arg_end);
	}
	else if (cmd->type == EXEC)
	{
		exec_cmd = (t_exec_cmd*)cmd;
		free(exec_cmd);
		// ft_free_2d(exec_cmd->arg_start);
		// ft_free_2d(exec_cmd->arg_end);
	}
}
void free_exit_status(t_exit_status *exit_sts)
{
	// free(exit_sts->exit_status);
	free(exit_sts);
}