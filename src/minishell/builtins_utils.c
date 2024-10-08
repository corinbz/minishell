/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:14:26 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/10 12:34:48 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*	where should you run the builtin:
	1 = inside parent process
	2 = inside child process
	3 = is not a builtin
*/
int	builtin_type(t_exec_cmd *cmd)
{
	if (!cmd->arg_start[0])
		return (3);
	if (ft_strncmp(cmd->arg_start[0], "exit", 5) == 0)
		return (2);
	if (ft_strncmp(cmd->arg_start[0], "env", 4) == 0)
		return (2);
	if (ft_strncmp(cmd->arg_start[0], "pwd", 4) == 0)
		return (2);
	if (ft_strncmp(cmd->arg_start[0], "echo", 5) == 0)
		return (2);
	if (ft_strncmp(cmd->arg_start[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->arg_start[0], "export", 7) == 0)
	{
		if (!cmd->arg_start[1])
			return (2);
		return (1);
	}
	if (ft_strncmp(cmd->arg_start[0], "unset", 6) == 0)
		return (1);
	return (3);
}

int	run_builtin_parent(t_exec_cmd *cmd, t_link_list **my_envp)
{
	if (ft_strncmp(cmd->arg_start[0], "cd", 2) == 0)
	{
		if (!cmd->arg_start[2])
			return (ft_cd(cmd->arg_start[1], *my_envp));
		print_to_stderr(cmd->arg_start[2], "no such file or directory");
		return (1);
	}
	if (ft_strncmp(cmd->arg_start[0], "export", 6) == 0)
	{
		return (ft_export(cmd->arg_start[1], *my_envp));
	}
	if (ft_strncmp(cmd->arg_start[0], "unset", 5) == 0)
	{
		return (ft_unset(cmd->arg_start[1], my_envp));
	}
	return (1);
}

int	run_builtin_child(t_exec_cmd *cmd, t_link_list *my_envp)
{
	int	exit_sts;

	if (ft_strncmp(cmd->arg_start[0], "exit", 5) == 0)
	{
		if (g_signal != 0)
			exit_sts = g_signal;
		else
			exit_sts = get_exit_sts(my_envp);
		return (ft_exit(cmd, exit_sts));
	}
	else if (ft_strncmp(cmd->arg_start[0], "env", 3) == 0)
		return (ft_env(my_envp));
	else if (ft_strncmp(cmd->arg_start[0], "pwd", 3) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd->arg_start[0], "echo", 4) == 0)
		return (ft_echo(cmd->arg_start[1], cmd->arg_start));
	else if (ft_strncmp(cmd->arg_start[0], "export", 6) == 0)
		return (ft_export(cmd->arg_start[1], my_envp));
	return (1);
}
