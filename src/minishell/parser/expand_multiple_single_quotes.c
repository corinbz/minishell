/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_multiple_single_quotes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:10:30 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/28 18:09:53 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *remove_single_quotes(char *quote_start, int quotes_amount)
{
	char *to_ret;
	char *temp;
	char *i;

	to_ret = quote_start;
	while (*to_ret)
		to_ret++;
	to_ret -= quotes_amount;
	temp = ft_strdup(quote_start);
	if (!temp)
		ft_panic("minishell: malloc failed\n");
	i = temp;
	while (*i)
	{
		if (*i != '\'')
		{
			*quote_start = *i;
			quote_start++;
		}
		i++;
	}
	*quote_start = '\0';
	free(temp);
	return (to_ret);
}

char	*expand_multiple_single_quotes(char *quote_start, t_link_list *env, int quotes_amount)
{
	char	*i;
	int		quotes;

	i = quote_start;
	quotes = 0;
	while (*i)
	{
		if (*i == '\'')
			quotes++;
		if (*i == '$' && quotes % 2 == 0)
		{
			i = expand_dollar_sign(i, env);
			quotes = 0;
		}	//todo elif "
		else
		{
			i++;
		}
	}
	return (remove_single_quotes(quote_start, quotes_amount)); //todo return shifted, return minus quotes am?
}

