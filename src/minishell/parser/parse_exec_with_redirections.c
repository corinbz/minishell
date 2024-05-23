/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_with_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:50:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/23 10:10:42 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*parse_base_exec(char **input)
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
			ft_panic("minishell: parse error\n");
		cmd_as_exec_cmd->argv[arguments_count] = token_start_pos;
		cmd_as_exec_cmd->eargv[arguments_count] = token_end_pos;
		arguments_count++;
		if (arguments_count >= MAX_ARGUMENTS)
			ft_panic("minishell: too many args\n");
		//todo parse redirection
	}
	cmd_as_exec_cmd->argv[arguments_count] = NULL;
	cmd_as_exec_cmd->eargv[arguments_count] = NULL;
	return (result_cmd);

}

t_cmd	*parse_exec_with_redirections(char **input)
{
	t_cmd	*cmd;

	cmd = parse_base_exec(input);
	//todo parsing recursion
}