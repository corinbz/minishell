/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:59:54 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/22 20:39:43 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *find_match_quote_end(char *quote_start)
{
	char	*matched_quote;
	char	*i;

	i = quote_start;
	while (*i)
		i++;
	while (i > quote_start)
	{
		if (*i == '\'')
			return (i);
		i--;
	}
	ft_panic("minishell: syntax error\n");
	return (NULL);
}

char	*expand_single_quote(char *quote_start)
{
	char	*quote_end;
	char	*to_ret;

	quote_end = find_match_quote_end(quote_start);
	to_ret = quote_end - 2;
	while (*quote_end)
	{
		*quote_end = *(quote_end + 1);
		quote_end++;
	}
	while (*quote_start)
	{
		*quote_start = *(quote_start + 1);
		quote_start++;
	}
	return (to_ret);
}

//todo if there is a quote inside a quote don't expand