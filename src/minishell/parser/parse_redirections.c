/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:30:09 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/04 14:42:32 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_redirections(t_cmd *cmd, char **input)
{
	char			token;
	t_tokens_pos	pos;

	while (is_token_ahead(input, "><"))
	{
		token = get_token(input, &pos.token_start, &pos.token_end);
		if (get_token(input, &pos.token_start, &pos.token_end) != 'a')
			ft_putstr_fd("minishell: syntax error\n", 2);
		if (token == '>')
			cmd = create_redir_cmd(cmd, pos, \
				O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (token == '+')
			cmd = create_redir_cmd(cmd, pos, \
				O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
		else if (token == '<')
			cmd = create_redir_cmd(cmd, pos, \
				O_RDONLY, STDIN_FILENO);
		else if (token == '-')
			cmd = create_heredoc_cmd(cmd, pos);
		else
			ft_panic("minishell: parse redirections error\n");
	}
	return (cmd);
}
