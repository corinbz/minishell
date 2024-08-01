/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:40:44 by corin             #+#    #+#             */
/*   Updated: 2024/08/01 20:34:49 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Utility function to execute a command in a child process
void	exec_child_process(char *cmd_path, char **args, char **envp)
{
	if (ft_strncmp((cmd_path), "Permission denied", ft_strlen(cmd_path)) == 0)
	{
		printf("%s: Permission denied\n", args[0]);
		exit(126);
	}
	else if (ft_strncmp((cmd_path), "Is a directory", ft_strlen(cmd_path)) == 0)
	{
		printf("%s: Is a directory\n", args[0]);
		exit(126);
	}
	else if (execve(cmd_path, args, envp) == -1)
	{
		printf("%s: no executable found\n", args[0]);
		exit(127);
	}
}

// Function to handle built-in commands
int	handle_builtin(t_exec_cmd *type_exec_cmd,
	t_link_list *my_envp, bool is_child)
{
	int	exitcode;

	if (builtin_type(type_exec_cmd) == 1)
	{
		exitcode = run_builtin_parent(type_exec_cmd, my_envp);
		if (is_child)
			ft_exit(NULL, exitcode);
		return (exitcode);
	}
	else if (builtin_type(type_exec_cmd) == 2)
	{
		exitcode = run_builtin_child(type_exec_cmd, my_envp);
		if (is_child)
			ft_exit(NULL, exitcode);
		return (exitcode);
	}
	return (-1);
}

// Function to execute external commands
int	exec_external(t_exec_cmd *type_exec_cmd, char **envp,
	t_link_list *my_envp, bool is_child)
{
	char	**paths;
	char	*cmd_path;
	int		pid;
	int		exitcode;

	paths = get_possible_paths(envp);
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	ft_free_2d(paths);
	if (!is_child)
	{
		pid = ft_fork();
		if (pid == 0)
			exec_child_process(cmd_path, type_exec_cmd->arg_start, envp);
		waitpid(pid, &exitcode, 0);
		exitcode = WEXITSTATUS(exitcode);
		return (free(cmd_path), exitcode);
	}
	exec_child_process(cmd_path, type_exec_cmd->arg_start, envp);
	return (free(cmd_path), 0);
}

int	exec_exec(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	t_exec_cmd	*type_exec_cmd;
	int			exitcode;

	type_exec_cmd = (t_exec_cmd *)cmd;
	if (!type_exec_cmd->arg_start[0])
		return (0);
	exitcode = handle_builtin(type_exec_cmd, my_envp, is_child);
	if (exitcode != -1)
		return (exitcode);
	envp = link_list_to_array(&my_envp);
	exitcode = exec_external(type_exec_cmd, envp, my_envp, is_child);
	ft_free_2d(envp);
	return (exitcode);
}

int	exec_cmd(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	int	exitcode;

	if (cmd->type == EXEC)
		exitcode = exec_exec(cmd, envp, my_envp, is_child);
	else if (cmd->type == REDIR)
		exitcode = exec_redir(cmd, envp, my_envp);
	else if (cmd->type == PIPE)
		exitcode = exec_pipe(cmd, envp, my_envp);
	else if (cmd->type == HEREDOC)
		exitcode = exec_heredoc(cmd, envp, my_envp);
	return (exitcode);
}
