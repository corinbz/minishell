/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:40:44 by corin             #+#    #+#             */
/*   Updated: 2024/07/20 10:41:14 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Utility function to execute a command in a child process
void exec_child_process(char *cmd_path, char **args, char **envp)
{
	if (execve(cmd_path, args, envp) == -1)
	{
		printf("%s: no executable found\n", args[0]);
		ft_free_2d(envp);
		ft_exit("127", g_signal);
	}
}

// Function to handle built-in commands
int handle_builtin(t_exec_cmd *type_exec_cmd, t_link_list *my_envp, bool is_child)
{
	int exitcode;

	if (builtin_type(type_exec_cmd) == 1)
	{
		exitcode = run_builtin_parent(type_exec_cmd, my_envp);
		if (is_child)
			ft_exit(NULL, exitcode);
		return exitcode;
	}
	else if (builtin_type(type_exec_cmd) == 2)
	{
		exitcode = run_builtin_child(type_exec_cmd, my_envp);
		if (is_child)
			exit(exitcode);
		return exitcode;
	}
	return -1;
}

// Function to execute external commands
int exec_external(t_exec_cmd *type_exec_cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	char **paths = get_possible_paths(envp);
	char *cmd_path = get_path(type_exec_cmd->arg_start[0], paths);

	if (!is_child)
	{
		int pid = ft_fork();
		if (pid == 0)
		{
			exec_child_process(cmd_path, type_exec_cmd->arg_start, envp);
		}
		int exitcode;
		waitpid(pid, &exitcode, 0);
		return exitcode;
	}

	exec_child_process(cmd_path, type_exec_cmd->arg_start, envp);
	return 0; // This line is never reached due to execve() or exit()
}

int exec_exec(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	t_exec_cmd *type_exec_cmd = (t_exec_cmd *)cmd;
	int exitcode;

	exitcode = handle_builtin(type_exec_cmd, my_envp, is_child);
	if (exitcode != -1)
		return exitcode;

	envp = link_list_to_array(&my_envp);
	exitcode = exec_external(type_exec_cmd, envp, my_envp, is_child);
	ft_free_2d(envp);
	return exitcode;
}


int exec_pipe(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	int end[2];
	if (pipe(end) < 0)
		ft_panic("pipe");

	pid_t left = ft_fork();
	if (left == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_panic("dup2 left");
		close(end[1]);
		exec_cmd(((t_pipe_cmd *)cmd)->left, envp, my_envp, true);
		exit(1);
	}

	pid_t right = ft_fork();
	if (right == 0)
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_panic("dup2 right");
		close(end[0]);
		exec_cmd(((t_pipe_cmd *)cmd)->right, envp, my_envp, true);
		exit(1);
	}

	close(end[0]);
	close(end[1]);
	int status;
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	return status;
}

int exec_cmd(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	int exitcode;
	if (cmd->type == EXEC)
		exitcode = exec_exec(cmd, envp, my_envp, is_child);
	else if (cmd->type == REDIR)
		exitcode = exec_redir(cmd, envp, my_envp);
	else if (cmd->type == PIPE)
		exitcode = exec_pipe(cmd, envp, my_envp);
	return exitcode;
}
