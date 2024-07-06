/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_multiple_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:10:30 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/03 09:18:49 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *remove_quotes(char *quote_start, int quotes_amount, t_quotes_enum quote_type)
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
		if ((quote_type == SINGLE_QUOTE && *i != '\'') || (quote_type == DOUBLE_QUOTE && *i != '"'))
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
//
//char	*expand_multiple_quotes(char *quote_start, t_link_list *env, t_quotes_enum quote_type, int quotes_amount)
//{
//	char	*i;
//	int		quotes;
//
//	i = quote_start;
//	quotes = 0;
//	while (*i)
//	{
//		if ((quote_type == SINGLE_QUOTE && *i == '\'') || (quote_type == DOUBLE_QUOTE && *i == '"'))
//			quotes++;
//		else if (*i == '$' && (quote_type == SINGLE_QUOTE && quotes % 2 == 0) || (quote_type == DOUBLE_QUOTE && quotes > 0))
//		{
//			i = expand_dollar_sign(i, env);
//			quotes = 0;
//		}
//		if (*i)
//			i++;
//	}
//	return (remove_quotes(quote_start, quotes_amount, quote_type));
//}
