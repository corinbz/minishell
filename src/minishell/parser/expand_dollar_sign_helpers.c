/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:19:48 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/06 20:20:49 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_var_with_val(char *dlr_start, char *dlr_end, char *val)
{
	char	*temp;
	char	*i;

	temp = ft_strdup(dlr_end);
	if (!temp)
		ft_panic("minishell: malloc failed\n");
	while (*val)
	{
		*dlr_start = *val;
		dlr_start++;
		val++;
	}
	i = temp;
	while (*i)
	{
		*dlr_start = *i;
		dlr_start++;
		i++;
	}
	*dlr_start = '\0';
	free(temp);
}

static char	*try_to_get_val_from_env(char *var, t_link_list *env)
{
	char	*to_ret;

	while (env)
	{
		if (ft_strncmp(env->param, var, ft_strlen(var)) == 0 && \
		((char *)env->param)[ft_strlen(var)] == '=')
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

static char	*extract_variable_name(char *dollar_pos)
{
	char		*var;
	int			i;
	const char	stop_chars[] = " \t\r\n\v\'\"$";

	var = malloc(32768);
	if (!var)
		ft_panic("minishell: malloc failed\n");
	i = 0;
	if (dollar_pos[i + 1] == '?')
	{
		var[i] = '?';
		i++;
	}
	else
	{
		while (dollar_pos[i + 1] && !ft_strchr(stop_chars, dollar_pos[i + 1]))
		{
			var[i] = dollar_pos[i + 1];
			i++;
		}
	}
	var[i] = '\0';
	return (var);
}

static void	expand_dollar_sign(char *dollar_pos, t_link_list **env)
{
	char	*var;
	char	*val;
	char	*dollar_end;

	var = extract_variable_name(dollar_pos);
	dollar_end = &dollar_pos[ft_strlen(var) + 1];
	val = try_to_get_val_from_env(var, *env);
	free(var);
	replace_var_with_val(dollar_pos, dollar_end, val);
	free(val);
}

bool	try_to_expand_dollar_sign(char *s, t_link_list **my_envp, t_state state)
{
	while (*s)
	{
		if (*s == '\'')
		{
			state.in_single = !state.in_single;
			if (state.in_double)
				state.single_in_double = !state.single_in_double;
		}
		if (*s == '"')
		{
			state.in_double = !state.in_double;
			if (state.in_single)
				state.double_in_single = !state.double_in_single;
		}
		if (*s == '$' && *(s + 1) != '\0' && *(s + 1) != '"' && \
		((!state.in_single && !state.in_double) || state.single_in_double || \
		(state.in_double && !state.double_in_single)))
		{
			expand_dollar_sign(s, my_envp);
			return (true);
		}
		else
			s++;
	}
	return (false);
}
