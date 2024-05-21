/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:37:04 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/21 04:27:59 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *parse_cmd(char *input)
{
	t_cmd	*cmd;
	char	*end;

	end = input + ft_strlen(input);
	cmd = parse_pipe(&input, end);
	//peek & panic if not the end after parsing
	//terminate cmd & return
}