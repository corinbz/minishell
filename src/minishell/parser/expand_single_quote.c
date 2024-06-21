/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:59:54 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/21 20:25:36 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_match_quote_end(char *quote_start)
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

void	expand_single_quote(char *quote_start)
{
	char	*quote_end;

	quote_end = find_match_quote_end(quote_start);
}
