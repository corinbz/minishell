/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:50:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 11:11:48 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_exec(char **input)
{
	t_cmd		*result_cmd;
	t_exec_cmd	*cmd_as_exec_cmd;
	int			arguments_count;
	char		token;
	char		*token_start_pos;
	char		*token_end_pos;

	result_cmd = create_exec_cmd();
	cmd_as_exec_cmd = (t_exec_cmd *)result_cmd;
	arguments_count = 0;
	while (!is_token_ahead(input, "|"))
	{
		token = get_token(input, &token_start_pos, &token_end_pos);
		if (token == '\0')
			break ;
		if (token != 'a')
			ft_panic("minishell: syntax error\n");
		cmd_as_exec_cmd->arg_start[arguments_count] = token_start_pos;
		cmd_as_exec_cmd->arg_end[arguments_count] = token_end_pos;
		arguments_count++;
		if (arguments_count >= MAX_ARGUMENTS)
			ft_panic("minishell: too many args\n");
		result_cmd = parse_redirections(result_cmd, input);
	}
	cmd_as_exec_cmd->arg_start[arguments_count] = NULL;
	cmd_as_exec_cmd->arg_end[arguments_count] = NULL;
	return (result_cmd);
}
