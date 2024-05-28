/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/27 10:48:524:42 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*mock_exec_cmd(void)
{
	t_exec_cmd	*sub_cmd;

	sub_cmd = malloc(sizeof(t_exec_cmd));
	sub_cmd->type = EXEC;
	sub_cmd->arg_start[0] = "ls";
	sub_cmd->arg_start[1] = "-l";
	sub_cmd->arg_start[2] = NULL;
	sub_cmd->arg_end[0] = sub_cmd->arg_start[0] + 2;
	sub_cmd->arg_end[1] = sub_cmd->arg_start[1] + 2;
	sub_cmd->arg_end[2] = NULL;
	return ((t_cmd *)sub_cmd);
}

t_cmd	*mock_redir_cmd(void)
{
	t_redir_cmd	*sub_cmd;

	sub_cmd = malloc(sizeof(t_redir_cmd));
	sub_cmd->type = REDIR;
	sub_cmd->sub_cmd = mock_exec_cmd();
	sub_cmd->token_start_pos = "output.txt";
	sub_cmd->token_end_pos = sub_cmd->token_start_pos + 10;
	sub_cmd->mode = O_WRONLY | O_CREAT;
	sub_cmd->fd = 1;
	sub_cmd->heredoc = false;
	return ((t_cmd *)sub_cmd);
}

t_cmd	*mock_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*sub_cmd;

	sub_cmd = malloc(sizeof(t_pipe_cmd));
	sub_cmd->type = PIPE;
	sub_cmd->left = mock_exec_cmd();
	sub_cmd->right = mock_redir_cmd();
	return ((t_cmd *)sub_cmd);
}
// void test_pipe(char **envp)
// {
// 	t_exec_cmd	*left;
// 	t_exec_cmd	*right;
// 	t_pipe_cmd	*pipe_cmd;
// 	int			end[2];
// 	pid_t		left_pid;
// 	pid_t		right_pid;
// 	int status;

// 	char **paths = get_possible_paths(envp);

// 	left = (t_exec_cmd*)create_exec_cmd();
// 	right = (t_exec_cmd*)create_exec_cmd();
// 	pipe_cmd = (t_pipe_cmd*)create_pipe_cmd((t_cmd*)left, (t_cmd*)right);
// 	left->arg_start[0] = "ls";
// 	right->arg_start[0] = "grep";
// 	right->arg_start[1] = "src";
// 	right->arg_start[2] = NULL;
// 	pipe(end);
// 	left_pid = fork();
// 	if(left_pid < 0)
// 		ft_panic("left fork failed\n");
// 	if(left_pid == 0)
// 	{
// 		printf("inside left pid\n");
// 		close(end[0]);
// 		char *path = get_path(pipe_cmd->left, paths);
// 		printf("path is %s\n", path);
// 		dup2(end[1], STDOUT_FILENO);
// 		if(execve(path, NULL, envp) == -1)
// 			ft_panic("left execve failed\n");
// 	}
// 	right_pid = fork();
// 	if(right_pid < 0)
// 		ft_panic("right fork failed\n");
// 	if(right_pid == 0)
// 	{
// 		close(end[1]);
// 		char *path = get_path(right->arg_start[0], paths);
// 		printf("path is %s\n", path);
// 		dup2(end[0], STDIN_FILENO);
// 		if(execve(path, right->arg_start, envp) == -1)
// 			ft_panic("right execve failed\n");
// 	}
// 	waitpid(left_pid, &status, 0);
// 	waitpid(right_pid, &status, 0);
// }

int exec_cmd(t_cmd *cmd, char **envp)
{
	char		**paths;
	char		*cmd_path;
	t_exec_cmd	*type_exec_cmd;
	t_redir_cmd	*type_redir_cmd;
	t_pipe_cmd	*type_pipe_cmd;
	int end[2];

	paths = get_possible_paths(envp);
	if (cmd == EXEC)
	{
		type_exec_cmd = (t_exec_cmd*)cmd;
		cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
		if(execve(cmd_path, NULL, envp) == -1)
		 {
			printf(2, "execve failed on %s\n", type_exec_cmd->arg_start[0]);
			return(1)
		 }
		return(0);
	}
	if(cmd == REDIR)
	{
		type_redir_cmd = (t_redir_cmd*)cmd;
		close(type_redir_cmd->fd);
		if(open(type_redir_cmd->token_start_pos, type_redir_cmd->mode) < 0)
		{
			printf(2, "failed to open %s\n", type_redir_cmd->token_start_pos);
			exit(1);
		}
		exec_cmd(type_redir_cmd->sub_cmd, envp);
		return (0);
	}
	if(cmd == PIPE)
	{
		type_pipe_cmd = (t_pipe_cmd*)cmd;
		if(pipe(end) < 0)
			panic("pipe");
		pid_t left;
		pid_t right;
		left = fork();
		if(left == 0)
		{
			close(end[0]);
			dup2(end[1], STDOUT_FILENO);
			close(end[1]);
			exec_cmd(type_pipe_cmd->left, envp);
		}

		right = fork();
		if(right == 0)
		{
			close(end[1]);
			dup2(end[0], STDIN_FILENO);
			close(end[0]);
			exec_cmd(type_pipe_cmd->right, envp);
		}
	}
}
int main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
	{
		ft_panic("This program does not accept arguments\n");
		exit(0);
	}
	test_pipe(envp);
	// while(1)
	// {
	// 	char *line = readline("my_shell$ ");
	// 	if (line == NULL || !ft_strncmp("exit", line, 5))
	// 	{
	// 		free(line);
	// 		exit(1);
	// 	}
	// 	add_history(line);
	// 	mock_data = parse_cmd(line);
	// 	printf("%d\n", mock_data->type);
	// 	// for (int i = 0; mock_exec->arg_start[i]; i++)
	// 	//  {
	// 	// 	printf("%s\n", mock_data->type);
	// 	//  }
	// 	free(mock_data);
	// 	free(line);
	// }
	// rl_clear_history();
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */