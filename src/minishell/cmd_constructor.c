/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:09:33 by corin             #+#    #+#             */
/*   Updated: 2024/08/02 04:45:17 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*create_redir_cmd(t_cmd *sub_cmd, t_tokens_pos pos, int mode, int fd)
{
	t_redir_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->sub_cmd = sub_cmd;
	cmd->token_start_pos = pos.token_start;
	cmd->token_end_pos = pos.token_end;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*create_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*create_heredoc_cmd(t_cmd *sub_cmd, t_tokens_pos pos)
{
	t_heredoc_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = HEREDOC;
	cmd->sub_cmd = sub_cmd;
	cmd->eof_start = pos.token_start;
	cmd->eof_end = pos.token_end;
	return ((t_cmd *)cmd);
}
