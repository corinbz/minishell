/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:48:05 by corin             #+#    #+#             */
/*   Updated: 2024/07/28 12:14:08 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe_cmd(t_pipe_cmd *pipe_cmd)
{
	free_full_cmd((t_cmd *)pipe_cmd->left);
	free_full_cmd((t_cmd *)pipe_cmd->right);
	free(pipe_cmd);
}

void	free_heredoc_cmd(t_heredoc_cmd *heredoc_cmd)
{
	free_full_cmd((t_cmd *)heredoc_cmd->sub_cmd);
	free(heredoc_cmd);
}

void	free_redir_cmd(t_redir_cmd *redir_cmd)
{
	free_full_cmd((t_cmd *)redir_cmd->sub_cmd);
	free(redir_cmd);
}

void	free_exec_cmd(t_exec_cmd *exec_cmd)
{
	free(exec_cmd);
}

void	free_full_cmd(t_cmd *cmd)
{
	if (cmd->type == PIPE)
		free_pipe_cmd((t_pipe_cmd *)cmd);
	else if (cmd->type == HEREDOC)
		free_heredoc_cmd((t_heredoc_cmd *)cmd);
	else if (cmd->type == REDIR)
		free_redir_cmd((t_redir_cmd *)cmd);
	else if (cmd->type == EXEC)
		free_exec_cmd((t_exec_cmd *)cmd);
}
