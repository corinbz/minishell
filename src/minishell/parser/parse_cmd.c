/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:37:04 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/23 10:10:47 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_cmd(char *input)
{
	t_cmd	*cmd;

	cmd = parse_pipe(&input);
	//peek & panic if not the end after parsing
	//terminate cmd & return
}