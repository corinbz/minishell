/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:25:27 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/06 08:23:31 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void remove_quotes(char *str, char *end)
{
	while (*end)
	{
		*end = *(end + 1);
		end++;
	}
	while (*str)
	{
		*str = *(str + 1);
		str++;
	}
}

static bool	try_to_find_matching_quotes_and_remove(char *str)
{
	bool	inside_double_quotes;
	char	*end;

	inside_double_quotes = false;
	while (*str)
	{
		if (*str == '"')
			inside_double_quotes = !inside_double_quotes;
		if (*str == '\'' && !inside_double_quotes)
			break ;
		str++;
	}
	if (!(*str))
		return (false);
	end = str + ft_strlen(str) - 1;
	while (end != str)
	{
		if (*end == '"')
			inside_double_quotes = !inside_double_quotes;
		if (*end == '\'' && !inside_double_quotes)
			break ;
		end--;
	}
	if (str == end)
		ft_panic("minishell: no matching quote\n");
	remove_quotes(str, end);
	return (true);
}

void	expand_single_quotes(char *i)
{
	while (try_to_find_matching_quotes_and_remove(i));
}