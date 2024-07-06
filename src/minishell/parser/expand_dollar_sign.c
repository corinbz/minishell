/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/06 11:13:45 by erybolov         ###   ########.fr       */
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
	bool	inside_single_quotes;
	bool	double_inside_single;
	bool	inside_double_quotes;
	bool	single_inside_double;

	inside_single_quotes = false;
	double_inside_single = false;
	inside_double_quotes = false;
	single_inside_double = false;
	while (*str)
	{
		if (*str == '\'')
		{
			inside_single_quotes = !inside_single_quotes;
			if (inside_double_quotes)
				single_inside_double = !single_inside_double;
		}
		if (*str == '"')
		{
			inside_double_quotes = !inside_double_quotes;
			if (inside_single_quotes)
				double_inside_single = !double_inside_single;
		}
		if (*str == '$' && ((!inside_single_quotes && !inside_double_quotes) || single_inside_double || (inside_double_quotes && !double_inside_single)))
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