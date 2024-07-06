/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_and_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:17:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/06 08:39:38 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *realloc_input(char **input)
{
	char	*i;

	i = malloc(32768); //dirty hack to avoid tedious calculations for now
	if (!i)
		ft_panic("minishell: malloc failed\n");
	ft_memcpy(i, *input, ft_strlen(*input) + 1);
	free(*input);
	*input = i;
	return (i);
}

static bool contains_character(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

void expand_env_vars_and_quotes(char **input, t_link_list *env)
{
	char	*i;

	i = *input;
	if (contains_character(i, '$'))
	{
		i = realloc_input(input);
		expand_dollar_signs(i, env);
	}
	if (contains_character(i, '"'))
		expand_double_quotes(i);
	if (contains_character(i, '\''))
		expand_single_quotes(i);
}

