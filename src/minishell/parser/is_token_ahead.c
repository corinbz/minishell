/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_ahead.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:51:24 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/23 09:18:22 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_token_ahead(char **input, char *tokens)
{
	skip_whitespaces(input);
	return (**input && ft_strchr(tokens, **input));
}

/*
 * Returns true if one of *tokens is ahead
 * Otherwise returns false
 */