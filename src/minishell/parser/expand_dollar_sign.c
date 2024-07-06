/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/06 09:22:25 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void replace_var_with_val(char *dollar_start, char *dollar_end, char *val)
{
	char *temp;
	char *i;

	temp = ft_strdup(dollar_end); // +1 ?
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

	var = malloc(32768); //todo allocate fixed size buffer on stack?
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

void	expand_dollar_signs(char *str, t_link_list *env)
{
	bool	inside_single_quotes;
	char	*str_start;

	inside_single_quotes = false;
	str_start = str;
	while (*str)
	{
		if (*str == '\'')
			inside_single_quotes = !inside_single_quotes;
		if (*str == '$' && !inside_single_quotes)
		{
			expand_dollar_sign(str, env);
			str = str_start;
			inside_single_quotes = false;
		}
		else
			str++;
	}
}