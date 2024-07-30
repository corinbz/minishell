/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:50:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/30 10:59:54 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_token(t_cmd **c, t_exec_cmd *c_exec, char **i, int *args)
{
	char	token;
	char	*token_start_pos;
	char	*token_end_pos;

	while (!is_token_ahead(i, "|"))
	{
		token = get_token(i, &token_start_pos, &token_end_pos);
		if (token == '\0')
			break ;
		if (token != 'a')
			ft_panic("minishell: syntax error\n");
		c_exec->arg_start[*args] = token_start_pos;
		c_exec->arg_end[*args] = token_end_pos;
		*token_end_pos = '\0';
		(*args)++;
		if (*args >= MAX_ARGUMENTS)
			ft_panic("minishell: too many args\n");
		*c = parse_redirections((t_cmd *)c_exec, i);
	}
}

t_cmd	*parse_exec(char **input)
{
	t_cmd		*result_cmd;
	t_exec_cmd	*cmd_as_exec_cmd;
	int			arguments_count;

	result_cmd = create_exec_cmd();
	cmd_as_exec_cmd = (t_exec_cmd *)result_cmd;
	arguments_count = 0;
	parse_token(&result_cmd, cmd_as_exec_cmd, input, &arguments_count);
	cmd_as_exec_cmd->arg_start[arguments_count] = NULL;
	cmd_as_exec_cmd->arg_end[arguments_count] = NULL;
	return (result_cmd);
}
