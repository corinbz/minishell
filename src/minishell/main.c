/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/11 18:09:50 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	t_minishell	*m;

	m = malloc(sizeof(t_minishell));
	minishell_run(m);
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * minishell_run is a program loop that will interact with user
 * also we have to implement cleanup (free etc) before we exit from main
 */