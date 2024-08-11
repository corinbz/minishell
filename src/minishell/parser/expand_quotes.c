/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:33:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/12 00:51:29 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	toggle_quote_state(char c, t_state *state)
{
	if (c == '\'')
	{
		if (!state->in_double)
		{
			state->in_single = !state->in_single;
			return (true);
		}
	}
	else if (c == '"')
	{
		if (!state->in_single)
		{
			state->in_double = !state->in_double;
			return (true);
		}
	}
	return (false);
}

static void	expand_quotes_loop(char *str_copy, char *str, t_state *state)
{
	while (*str_copy)
	{
		if (!toggle_quote_state(*str_copy, state))
		{
			*str = *str_copy;
			str++;
		}
		str_copy++;
	}
	*str = '\0';
}

static void	replace_spaces_to_keep(char *str, t_state *state)
{
	while (*str)
	{
		toggle_quote_state(*str, state);
		if (*str == '<' || *str == '>' || *str == '|' || *str == ' ')
		{
			if (*str == '<' && (state->in_single || state->in_double))
				*str = 28;
			if (*str == '>' && (state->in_single || state->in_double))
				*str = 29;
			if (*str == '|' && (state->in_single || state->in_double))
				*str = 30;
			if (*str == ' ' && (state->in_single || state->in_double))
				*str = 31;
		}
		str++;
	}
}

static void	reset_state(t_state *state)
{
	state->in_single = false;
	state->double_in_single = false;
	state->in_double = false;
	state->single_in_double = false;
}

void	expand_quotes(char *str)
{
	t_state	state;
	char	*str_copy;

	reset_state(&state);
	replace_spaces_to_keep(str, &state);
	str_copy = ft_strdup(str);
	if (!str_copy)
		ft_panic("minishell: malloc failed\n");
	reset_state(&state);
	expand_quotes_loop(str_copy, str, &state);
	free(str_copy);
}
