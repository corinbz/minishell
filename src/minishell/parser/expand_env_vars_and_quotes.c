/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_and_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:17:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/21 21:35:37 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_env_vars_and_quotes(char **input, t_link_list *env)
{
	char	*str;

	str = *input;
	while (*str)
	{
		if (*str == '$')
			str = expand_dollar_sign(input, str, env);
		if (*str == '\'')
			expand_single_quote(str); //todo wip
//		if (str[i] == '"')
//			expand_double_quote(input, &str[i]);
		str++;
	}
}

//wrong syntax if the same symbol not found