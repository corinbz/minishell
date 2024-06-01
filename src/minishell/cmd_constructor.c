/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:09:33 by corin             #+#    #+#             */
/*   Updated: 2024/06/01 15:01:46 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0 , sizeof(*cmd));
	cmd->type = EXEC;
	return (t_cmd*)cmd;
}

t_cmd	*create_redir_cmd(t_cmd *sub_cmd, char *file, char *efile, int mode, int fd, bool heredoc)
{
	t_redir_cmd	*cmd;
	
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->sub_cmd = sub_cmd;
	cmd->token_start_pos = file;
	cmd->token_end_pos = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	if (heredoc)
		cmd->heredoc = true;
	else
		cmd->heredoc = false;
	return (t_cmd*)cmd;
}

t_cmd	*create_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
}
