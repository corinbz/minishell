/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:44:50 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 14:03:12 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_pipe(char **input)
{
	t_cmd	*cmd;

	cmd = parse_exec(input);
	if (is_token_ahead(input, "|"))
	{
		get_token(input, NULL, NULL);
		cmd = create_pipe_cmd(cmd, parse_pipe(input));
	}
	return (cmd);
}

