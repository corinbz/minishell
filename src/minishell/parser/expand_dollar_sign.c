/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/24 11:40:03 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void replace_var_with_val(char *dollar_start, char *dollar_end, char *val)
{
	char *temp;
	char *i;

	temp = ft_strdup(dollar_end);
	if (!temp)
		ft_panic("minishell: malloc failed\n");
	while (*val)
	{
		*dollar_start = *val;
		dollar_start++;
		val++;
	}
	i = temp;
	while (*i)
	{
		*dollar_start = *i;
		dollar_start++;
		i++;
	}
	*dollar_start = '\0';
	free(temp);
}

static char *try_to_get_val_from_env(char *var, t_link_list *env)
{
	char *to_ret;

	while (env)
	{
		if (ft_strncmp(env->param, var, ft_strlen(var)) == 0 && env->param[ft_strlen(var)] == '=')
		{
			to_ret = ft_strdup(env->param + ft_strlen(var) + 1);
			if (!to_ret)
				ft_panic("minishell: ft_strdup failed\n");
			return (to_ret);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

static void expand_dollar_sign(char *dollar_pos, t_link_list *env)
{
	char *var;
	char *val;
	char *dollar_end;
	int i;
	const char	stop_chars[] = " \t\r\n\v\'\"$";

	var = malloc(32768);
	if (!var)
		ft_panic("minishell: malloc failed\n");
	i = 0;
	while (dollar_pos[i + 1] && !ft_strchr(stop_chars, dollar_pos[i + 1]))
	{
		var[i] = dollar_pos[i + 1];
		i++;
	}
	var[i] = '\0';
	dollar_end = &dollar_pos[i + 1];
	val = try_to_get_val_from_env(var, env);
	free(var);
	replace_var_with_val(dollar_pos, dollar_end, val);
	free(val);
}

static bool	try_to_expand_dollar_sign(char *str, t_link_list *env)
{
	t_parser_quotes_state state;

	state.inside_single_quotes = false;
	state.double_inside_single = false;
	state.inside_double_quotes = false;
	state.single_inside_double = false;
	while (*str)
	{
		if (*str == '\'')
		{
			state.inside_single_quotes = !state.inside_single_quotes;
			if (state.inside_double_quotes)
				state.single_inside_double = !state.single_inside_double;
		}
		if (*str == '"')
		{
			state.inside_double_quotes = !state.inside_double_quotes;
			if (state.inside_single_quotes)
				state.double_inside_single = !state.double_inside_single;
		}
		if (*str == '$' && ((!state.inside_single_quotes && !state.inside_double_quotes) || state.single_inside_double || (state.inside_double_quotes && !state.double_inside_single)))
		{
			expand_dollar_sign(str, env);
			return (true);
		}
		else
			str++;
	}
	return (false);
}

void	expand_dollar_signs(char *str, t_link_list *env)
{
	while (try_to_expand_dollar_sign(str, env));
}