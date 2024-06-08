/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:51:21 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/08 17:12:03 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int	run_cmd(char *cmd, t_link_list *envp)
// {
// 	if(ft_strncmp(cmd, "cd", 2) == 0)
// 		ft_cd();
// 	if(ft_strncmp(cmd, "exit", 4) == 0)
// 		ft_exit();
// 	if(ft_strncmp(cmd, "env", 3) == 0)
// 		ft_env(envp);
// 	if(ft_strncmp(cmd, "pwd", 3) == 0)
// 		ft_pwd();
// 	if(ft_strncmp(cmd, "echo", 4) == 0)
// 		ft_echo(,false);
// 	if(ft_strncmp(cmd, "export", 6) == 0)
// 		ft_export(cmd);
// }
int	exec_exec(t_cmd *cmd, char **envp)
{
	char		**paths;
	char		*cmd_path;
	t_exec_cmd	*type_exec_cmd;
	t_link_list	*builtins;
	
	int i = 0;
	builtins = create_builtin_lst();
	while(builtins)
	{
		if(strncmp(cmd, builtins->param, ft_strlen(cmd)) == 0)
			{
				
			}
	}
	paths = get_possible_paths(envp);
	type_exec_cmd = (t_exec_cmd*)cmd;
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
		{
		printf("execve failed on %s\n", type_exec_cmd->arg_start[0]);
		return(1);
		}
	return(0);
}

int exec_redir(t_cmd *cmd, char **envp)
{
	t_redir_cmd	*type_redir_cmd;
	int			new_fd;
	char		*error;

	type_redir_cmd = (t_redir_cmd*)cmd;
	close(type_redir_cmd->fd);
	// if(type_redir_cmd->heredoc)
	// {
	// 	char *eof = "eof";
	// 	ft_heredoc(eof, envp);
	// }
	new_fd = open(type_redir_cmd->token_start_pos, type_redir_cmd->mode, DEFAULT_CHMOD);
	if(new_fd < 0)
	{
		error = "failed to create file\n";
		ft_putstr_fd(error,2);
		return(1);
	}
	exec_cmd(type_redir_cmd->sub_cmd, envp);
	close(new_fd);
	return (0);
}

int exec_pipe(t_cmd *cmd, char **envp)
{
	t_pipe_cmd	*type_pipe_cmd;
	int			end[2];
	pid_t		left;
	pid_t		right;
	int			status;
	int			status2;

	type_pipe_cmd = (t_pipe_cmd*)cmd;
	if(pipe(end) < 0)
		ft_panic("pipe");
	left = ft_fork();
	if(left == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		exec_cmd(type_pipe_cmd->left, envp);
	}
	right = ft_fork();
	if(right == 0)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		exec_cmd(type_pipe_cmd->right, envp);
	}
	close(end[0]);
	close(end[1]);
	waitpid(left, &status, 0);
	waitpid(right, &status2, 0);
	return(0);
}
int exec_cmd(t_cmd *cmd, char **envp)
{

	if (cmd->type == EXEC)
		exec_exec(cmd, envp);
	if(cmd->type == REDIR)
		exec_redir(cmd, envp);
	if(cmd->type == PIPE)
		exec_pipe(cmd, envp);
	return(0);
}