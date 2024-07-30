/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:44:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/30 11:35:05 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_heredoc_cmd(t_cmd *cmd)
{
	t_redir_cmd	*redir_cmd;
	t_pipe_cmd	*pipe_cmd;

	if (cmd->type == REDIR)
	{
		redir_cmd = (t_redir_cmd *)cmd;
		return (is_heredoc_cmd(redir_cmd->sub_cmd));
	}
	if (cmd->type == PIPE)
	{
		pipe_cmd = (t_pipe_cmd *)cmd;
		return (is_heredoc_cmd(pipe_cmd->left) || \
		is_heredoc_cmd(pipe_cmd->right));
	}
	if (cmd->type == HEREDOC)
		return (true);
	return (false);
}
