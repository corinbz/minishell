/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 13:21:16 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*mock_exec_cmd(void)
// {
// 	t_exec_cmd	*sub_cmd;

// 	sub_cmd = malloc(sizeof(t_exec_cmd));
// 	sub_cmd->type = EXEC;
// 	sub_cmd->arg_start[0] = "ls";
// 	sub_cmd->arg_start[1] = "-l";
// 	sub_cmd->arg_start[2] = NULL;
// 	sub_cmd->arg_end[0] = sub_cmd->arg_start[0] + 2;
// 	sub_cmd->arg_end[1] = sub_cmd->arg_start[1] + 2;
// 	sub_cmd->arg_end[2] = NULL;
// 	return ((t_cmd *)sub_cmd);
// }

// t_cmd	*mock_redir_cmd(void)
// {
// 	t_redir_cmd	*sub_cmd;

// 	sub_cmd = malloc(sizeof(t_redir_cmd));
// 	sub_cmd->type = REDIR;
// 	sub_cmd->sub_cmd = mock_exec_cmd();
// 	sub_cmd->token_start_pos = "output.txt";
// 	sub_cmd->token_end_pos = sub_cmd->token_start_pos + 10;
// 	sub_cmd->mode = O_WRONLY | O_CREAT;
// 	sub_cmd->fd = 1;
// 	sub_cmd->heredoc = false;
// 	return ((t_cmd *)sub_cmd);
// }

// t_cmd	*mock_pipe_cmd(void)
// {
// 	t_pipe_cmd	*sub_cmd;

// 	sub_cmd = malloc(sizeof(t_pipe_cmd));
// 	sub_cmd->type = PIPE;
// 	sub_cmd->left = mock_exec_cmd();
// 	sub_cmd->right = mock_redir_cmd();
// 	return ((t_cmd *)sub_cmd);
// }

// t_cmd	*parse_cmd(char *input)
// {
// 	if (strcmp(input, "exec") == 0)
// 		return mock_exec_cmd();
// 	else if (strcmp(input, "redir") == 0)
// 		return mock_redir_cmd();
// 	else if (strcmp(input, "pipe") == 0)
// 		return mock_pipe_cmd();
// 	else
// 		return NULL;
// }

int main(int argc, char **argv, char **envp)
{
	printf("ac is %d and program name is %s\n",argc, argv[0] );
	envp[0] = NULL;
	ft_pwd();
	while(1)
	{
		char *line = readline("my_shell$ ");
		if (line == NULL || !ft_strncmp("exit", line, 5))
		{
			free(line);
			exit(1);
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */