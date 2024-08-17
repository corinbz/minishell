/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:20:19 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/11 02:14:16 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	prepare_exec_cmd(t_exec_cmd *c)
{
	int	i;
	int	j;

	i = 0;
	while (c->arg_start[i])
	{
		j = 0;
		while (c->arg_start[i][j])
		{
			if (c->arg_start[i][j] == 28)
				c->arg_start[i][j] = '<';
			if (c->arg_start[i][j] == 29)
				c->arg_start[i][j] = '>';
			if (c->arg_start[i][j] == 30)
				c->arg_start[i][j] = '|';
			if (c->arg_start[i][j] == 31)
				c->arg_start[i][j] = ' ';
			j++;
		}
		i++;
	}
}

static void	prepare_redir_cmd(t_redir_cmd *c)
{
	int	i;

	i = 0;
	while (c->token_start_pos[i])
	{
		if (c->token_start_pos[i] == 28)
			c->token_start_pos[i] = '<';
		if (c->token_start_pos[i] == 29)
			c->token_start_pos[i] = '>';
		if (c->token_start_pos[i] == 30)
			c->token_start_pos[i] = '|';
		if (c->token_start_pos[i] == 31)
			c->token_start_pos[i] = ' ';
		i++;
	}
	prepare_cmd(c->sub_cmd);
}

static void	prepare_pipe_cmd(t_pipe_cmd *c)
{
	prepare_cmd(c->left);
	prepare_cmd(c->right);
}

static void	prepare_heredoc_cmd(t_heredoc_cmd *c)
{
	int	i;

	i = 0;
	while (c->eof_start[i])
	{
		if (c->eof_start[i] == 28)
			c->eof_start[i] = '<';
		if (c->eof_start[i] == 29)
			c->eof_start[i] = '>';
		if (c->eof_start[i] == 30)
			c->eof_start[i] = '|';
		if (c->eof_start[i] == 31)
			c->eof_start[i] = ' ';
		i++;
	}
	prepare_cmd(c->sub_cmd);
}

void	prepare_cmd(t_cmd *cmd)
{
	t_exec_cmd		*cmd_as_exec_cmd;
	t_redir_cmd		*cmd_as_redir_cmd;
	t_pipe_cmd		*cmd_as_pipe_cmd;
	t_heredoc_cmd	*cmd_as_heredoc_cmd;

	cmd_as_exec_cmd = (t_exec_cmd *)cmd;
	cmd_as_redir_cmd = (t_redir_cmd *)cmd;
	cmd_as_pipe_cmd = (t_pipe_cmd *)cmd;
	cmd_as_heredoc_cmd = (t_heredoc_cmd *)cmd;
	if (cmd->type == EXEC)
		prepare_exec_cmd(cmd_as_exec_cmd);
	if (cmd->type == REDIR)
		prepare_redir_cmd(cmd_as_redir_cmd);
	if (cmd->type == PIPE)
		prepare_pipe_cmd(cmd_as_pipe_cmd);
	if (cmd->type == HEREDOC)
		prepare_heredoc_cmd(cmd_as_heredoc_cmd);
}
