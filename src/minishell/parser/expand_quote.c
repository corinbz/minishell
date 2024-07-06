/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:59:54 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/03 09:04:36 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//
//static char *find_match_quote_end(char *quote_start, t_quotes_enum quote_type)
//{
//	char	*i;
//
//	i = quote_start;
//	while (*i)
//		i++;
//	while (i > quote_start)
//	{
//		if ((quote_type == SINGLE_QUOTE && *i == '\'') || (quote_type == DOUBLE_QUOTE && *i == '"'))
//			return (i);
//		i--;
//	}
//	ft_panic("minishell: syntax error\n");
//	return (NULL);
//}
//
//static int	calculate_quotes_amount(char *str, t_quotes_enum quote_type)
//{
//	int	i;
//
//	i = 0;
//	while (*str)
//	{
//		if ((quote_type == SINGLE_QUOTE && *str == '\'') || (quote_type == DOUBLE_QUOTE && *str == '"'))
//			i++;
//		str++;
//	}
//	return (i);
//}
//
//static char	*expand_two_quotes(char *quote_start, t_quotes_enum quote_type)
//{
//	char		*quote_end;
//	char		*to_ret;
//
//	quote_end = find_match_quote_end(quote_start, quote_type);
//	to_ret = quote_end - 2;
//	while (*quote_end)
//	{
//		*quote_end = *(quote_end + 1);
//		quote_end++;
//	}
//	while (*quote_start)
//	{
//		*quote_start = *(quote_start + 1);
//		quote_start++;
//	}
//	return (to_ret);
//}
//
//char *expand_quote(char *quote_start, t_link_list *env, t_quotes_enum quote_type)
//{
//	int	quotes_amount;
//
//	quotes_amount = calculate_quotes_amount(quote_start, quote_type);
//	if (quotes_amount < 2 || quotes_amount % 2 != 0)
//		ft_panic("minishell: syntax error\n");
//	else if (quotes_amount == 2)
//		return (expand_two_quotes(quote_start, quote_type));
//	else
//		return (expand_multiple_quotes(quote_start, env, quote_type, quotes_amount));
//	return (ft_panic("minishell: unknown error\n"), NULL);
//}
