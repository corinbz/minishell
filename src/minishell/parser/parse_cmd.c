/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:37:04 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/27 10:44:49 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_cmd(char *input)
{
	t_cmd	*cmd;

	cmd = parse_pipe(&input);
	skip_whitespaces(&input);
	if (*input)
		ft_panic("minishell: parse leftovers\n");
	null_terminate_cmd(cmd);
	return (cmd);
}
