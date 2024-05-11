/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:39:34 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/11 18:05:25 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../../libft/libft.h"

typedef struct s_minishell
{
	t_list	*input_history;
}	t_minishell;

void	minishell_run(t_minishell m);

#endif
