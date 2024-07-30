/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:33:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/30 11:28:27 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_quotes_loop(char *str_copy, char *str, t_state state)
{
	while (*str_copy)
	{
		if (*str_copy == '\'')
		{
			if (!state.in_double)
			{
				state.in_single = !state.in_single;
				str_copy++;
				continue ;
			}
		}
		else if (*str_copy == '"')
		{
			if (!state.in_single)
			{
				state.in_double = !state.in_double;
				str_copy++;
				continue ;
			}
		}
		*str = *str_copy;
		str++;
		str_copy++;
	}
	*str = '\0';
}

void	expand_quotes(char *str)
{
	t_state	state;
	char	*str_copy;

	state.in_single = false;
	state.in_double = false;
	str_copy = ft_strdup(str);
	if (!str_copy)
		ft_panic("minishell: malloc failed\n");
	expand_quotes_loop(str_copy, str, state);
	free(str_copy);
}
