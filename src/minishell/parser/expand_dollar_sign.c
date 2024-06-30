/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/28 18:10:15 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *replace_var_with_val(char *dollar_start, char *dollar_end, char *val)
{
	char *temp;
	char *i;
	char *to_ret;

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
	to_ret = dollar_start;
	while (*i)
	{
		*dollar_start = *i;
		dollar_start++;
		i++;
	}
	*dollar_start = '\0';
	free(temp);
	return (to_ret);
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

char *expand_dollar_sign(char *dollar_pos, t_link_list *env)
{
	char *var;
	char *val;
	char *dollar_end;
	char *to_ret;
	int i;
	const char	stop_chars[] = " \t\r\n\v\'\"$";

	var = malloc(ft_strlen(dollar_pos) * 10);
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
	to_ret = replace_var_with_val(dollar_pos, dollar_end, val);
	free(val);
	return (to_ret);
}
