/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_and_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:17:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/11 01:18:37 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*realloc_input(char **input)
{
	char	*i;
	char	*old_input;

	i = malloc(32768);
	old_input = *input;
	if (!i)
		ft_panic("minishell: malloc failed\n");
	ft_memcpy(i, *input, ft_strlen(*input) + 1);
	*input = i;
	free(old_input);
	return (i);
}

static bool	contains_character(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

void	expand_env_vars_and_quotes(char **input, t_link_list **my_envp)
{
	char	*i;

	i = *input;
	if (contains_character(i, '$'))
	{
		i = realloc_input(input);
		expand_dollar_signs(i, my_envp);
	}
	if (contains_character(i, '"') || contains_character(i, '\''))
		expand_quotes(i);
}
