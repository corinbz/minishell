/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:39:50 by corin             #+#    #+#             */
/*   Updated: 2024/08/06 19:41:06 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// depending on the mode, we clean the file or append to it
static void	handle_redirection_mode(t_redir_cmd *type_redir_cmd)
{
	int	new_fd;

	if (type_redir_cmd->mode == (O_WRONLY | O_CREAT | O_TRUNC))
	{
		new_fd = open(type_redir_cmd->token_start_pos,
				type_redir_cmd->mode, DEFAULT_CHMOD);
		write(new_fd, "", 0);
		close(new_fd);
	}
	else if (type_redir_cmd->mode == (O_WRONLY | O_CREAT | O_APPEND))
	{
		new_fd = open(type_redir_cmd->token_start_pos,
				type_redir_cmd->mode, DEFAULT_CHMOD);
		close(new_fd);
	}
	else if (type_redir_cmd->mode == (O_RDONLY))
	{
		new_fd = open(type_redir_cmd->token_start_pos, type_redir_cmd->mode);
		close(new_fd);
	}
}

// open the file and redirect the file descriptor
static int	handle_redirection(t_redir_cmd *type_redir_cmd)
{
	int	new_fd;

	new_fd = open(type_redir_cmd->token_start_pos,
			type_redir_cmd->mode, DEFAULT_CHMOD);
	if (new_fd < 0)
	{
		ft_putstr_fd("failed to acces file\n", 2);
		return (-1);
	}
	if (dup2(new_fd, type_redir_cmd->fd) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		close(new_fd);
		return (-1);
	}
	close(new_fd);
	return (0);
}

static int	process_redirections(t_redir_cmd *type_redir_cmd)
{
	while (type_redir_cmd->sub_cmd->type == REDIR)
	{
		type_redir_cmd = (t_redir_cmd *)type_redir_cmd->sub_cmd;
		if (handle_redirection(type_redir_cmd) == -1)
			return (1);
		handle_redirection_mode(type_redir_cmd);
	}
	return (0);
}

int	exec_redir(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	t_redir_cmd	*type_redir_cmd;
	t_redir_cmd	*end_destination;
	int			exitcode;
	int			original_stdout_fd;
	int			original_stdin_fd;

	type_redir_cmd = (t_redir_cmd *)cmd;
	end_destination = (t_redir_cmd *)cmd;
	if (save_original_fds(&original_stdout_fd, &original_stdin_fd) != 0)
		return (1);
	if (process_redirections(type_redir_cmd) != 0)
		return (close(original_stdin_fd), close(original_stdout_fd), 1);
	while (type_redir_cmd->sub_cmd->type == REDIR)
		type_redir_cmd = (t_redir_cmd *)type_redir_cmd->sub_cmd;
	if (handle_redirection(end_destination) == -1)
		return (close(original_stdin_fd), close(original_stdout_fd), 1);
	exitcode = exec_cmd(type_redir_cmd->sub_cmd, envp, &my_envp, false);
	if (restore_original_fds(original_stdout_fd, original_stdin_fd) != 0)
		return (1);
	return (exitcode);
}
