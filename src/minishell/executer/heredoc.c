/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:00:23 by corin             #+#    #+#             */
/*   Updated: 2024/08/06 20:24:34 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_input(t_heredoc_cmd *heredoc, const char *new_eof,
	t_link_list *my_envp)
{
	char	*input;
	char	*input_newline;

	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			close_temp_fd_and_unlink(heredoc->temp_fd, "heredoc");
			return (1);
		}
		if (ft_strncmp(input, new_eof, ft_strlen(new_eof)) == 0)
			return (free(input), 0);
		else
		{
			input_newline = ft_strjoin(input, "\n");
			if (!input_newline)
				return (free(input), 1);
			expand_dollar_signs(input_newline, &my_envp);
			ft_putstr_fd(input_newline, heredoc->temp_fd);
			free(input_newline);
		}
		free(input);
	}
}

// Redirect STDIN to heredoc file
static int	redirect_stdin_to_heredoc(int original_stdin, t_cmd *sub_cmd,
	char **envp, t_link_list *my_envp)
{
	int	new_fd;
	int	exitcode;

	new_fd = open("heredoc", O_RDONLY);
	if (new_fd < 0)
		return (perror("Error reopening heredoc file"), 1);
	if (dup2(new_fd, STDIN_FILENO) < 0)
	{
		perror("Error redirecting STDIN");
		close(new_fd);
		return (1);
	}
	close(new_fd);
	unlink("heredoc");
	exitcode = exec_cmd(sub_cmd, envp, &my_envp, false);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	return (exitcode);
}

// Execute the heredoc command
int	exec_heredoc(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	t_heredoc_cmd	*heredoc;
	char			*new_eof;
	int				original_stdin;

	heredoc = (t_heredoc_cmd *)cmd;
	new_eof = create_new_eof(heredoc->eof_start, heredoc->eof_end);
	if (!new_eof)
		return (perror("Error creating new EOF string"), 1);
	if (open_heredoc_file(&heredoc->temp_fd) != 0)
		return (free(new_eof), 1);
	if (duplicate_stdin(&original_stdin) != 0)
	{
		close_temp_fd_and_unlink(heredoc->temp_fd, "heredoc");
		free(new_eof);
		return (1);
	}
	if (handle_heredoc_input(heredoc, new_eof, my_envp) != 0)
		return (close(original_stdin), free(new_eof), 1);
	close(heredoc->temp_fd);
	if (redirect_stdin_to_heredoc(original_stdin,
			heredoc->sub_cmd, envp, my_envp) != 0)
		return (free(new_eof), 1);
	free(new_eof);
	return (0);
}
