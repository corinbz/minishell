/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:06:39 by corin             #+#    #+#             */
/*   Updated: 2024/08/11 01:19:37 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_terminal(struct termios *saved_termios,
	struct termios *raw_termios)
{
	tcgetattr(STDIN_FILENO, saved_termios);
	*raw_termios = *saved_termios;
	cfmakeraw(raw_termios);
}

void	reset_terminal(const struct termios *saved_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, saved_termios);
}

void	handle_eof(t_exit_status *exit_sts)
{
	printf("exit\n");
	if (g_signal != 0)
		exit(g_signal);
	exit(exit_sts->exit_status);
}

static void	process_and_execute_command(char *input, char **envp,
	t_link_list **my_envp, t_exit_status *exit_sts)
	{
	t_cmd	*cmd;

	add_exit_status_to_envp(my_envp, exit_sts);
	add_history(input);
	expand_env_vars_and_quotes(&input, my_envp);
	cmd = parse_cmd(input);
	prepare_cmd(cmd);
	exit_sts->exit_status = exec_cmd(cmd, envp, my_envp, false);
	g_signal = 0;
	free(input);
	free_full_cmd(cmd);
}

void	read_and_process_input(char **envp, t_link_list **my_envp,
	t_exit_status *exit_sts)
	{
	char	*input;

	input = readline("minishell: ");
	rl_on_new_line();
	if (!input)
		handle_eof(exit_sts);
	if (input && *input)
		process_and_execute_command(input, envp, my_envp, exit_sts);
}
