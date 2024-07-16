/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:33:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/07 11:10:02 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_quotes(char *str)
{
	t_parser_quotes_state state;
	char	*str_copy;
	char 	*str_copy_ptr;

	state.inside_single_quotes = false;
	state.inside_double_quotes = false;
	str_copy = ft_strdup(str);
	if (!str_copy)
		ft_panic("minishell: malloc failed\n");
	str_copy_ptr = str_copy;
	while (*str_copy)
	{
		if (*str_copy == '\'')
		{
			state.inside_single_quotes = !state.inside_single_quotes;
			if (state.inside_double_quotes)
			{
				*str = *str_copy;
				str++;
			}
			str_copy++;
		}
		else if (*str_copy == '"')
		{
			state.inside_double_quotes = !state.inside_double_quotes;
			if (state.inside_single_quotes)
			{
				*str = *str_copy;
				str++;
			}
			str_copy++;
		}
		else
		{
			*str = *str_copy;
			str++;
			str_copy++;
		}
	}
	*str = '\0';
	free(str_copy_ptr);
}