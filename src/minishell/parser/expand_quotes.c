/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:33:26 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/11 01:15:53 by erybolov         ###   ########.fr       */
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
		if (toggle_quote_state(*str_copy, state))
			str_copy++;
		*str = *str_copy;
		str++;
		str_copy++;
	}
	*str = '\0';
}

static void	replace_spaces_to_keep(char *str, t_state *state)
{
	int	i;

	i = 0;
	while (str[i])
	{
		toggle_quote_state(str[i], state);
		if (str[i] == ' ')
		{
			if (state->in_single || state->in_double)
				str[i] = 31;
		}
		i++;
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
