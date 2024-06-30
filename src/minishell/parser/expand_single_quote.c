/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:59:54 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/28 16:42:31 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *find_match_quote_end(char *quote_start)
{
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

static int	calculate_single_quotes_amount(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'')
			i++;
		str++;
	}
	return (i);
}

static char	*expand_two_single_quotes(char *quote_start)
{
	char		*quote_end;
	char		*to_ret;

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

char	*expand_single_quote(char *quote_start, t_link_list *env)
{
	int	single_quotes_amount;

	single_quotes_amount = calculate_single_quotes_amount(quote_start);
	if (single_quotes_amount < 2 || single_quotes_amount % 2 != 0)
		ft_panic("minishell: syntax error\n");
	else if (single_quotes_amount == 2)
		return (expand_two_single_quotes(quote_start));
	else
		return (expand_multiple_single_quotes(quote_start, env, single_quotes_amount));
	return (ft_panic("minishell: unknown error\n"), NULL);
}



//todo if there is a quote inside a quote don't expand