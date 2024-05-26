/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:37:04 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/26 16:12:04 by erybolov         ###   ########.fr       */
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
