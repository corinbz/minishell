/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:44:50 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 11:18:10 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_pipe(char **input)
{
	t_cmd	*cmd;

	cmd = parse_exec(input);

	return (cmd);
	//todo unwind parse recursion
}

