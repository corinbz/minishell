/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_with_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:50:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/21 04:27:20 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd *parse_base_exec(char **input, char *end)
{
	t_cmd		*result_cmd;
	t_exec_cmd	*cmd_as_exec_cmd;

	result_cmd = create_exec_cmd();
	cmd_as_exec_cmd = (t_exec_cmd *)result_cmd;

	//todo fill the structure, parse the rest

	return (result_cmd);

}

t_cmd *parse_exec_with_redirections(char **input, char *end)
{
	t_cmd	*cmd;

	cmd = parse_base_exec(input, end);
	//todo parsing recursion
}