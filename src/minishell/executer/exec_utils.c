/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:31:39 by corin             #+#    #+#             */
/*   Updated: 2024/07/28 12:30:57 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*display message to stderror then exit(1)*/
noreturn void	ft_panic(const char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

//fork with error handling
pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_panic("Fork failed\n");
	return (pid);
}

t_link_list	*create_builtin_lst(void)
{
	t_link_list	*builtins;
	char		*temp;
	char		**split;
	int			i;

	i = 0;
	builtins = ft_calloc(1, sizeof(builtins));
	temp = "cd exit env pwd echo export unset";
	split = ft_split(temp, ' ');
	if (!split)
		return (builtins);
	while (split[i])
	{
		ft_export(split[i], builtins);
		i++;
	}
	ft_free_2d(split);
	return (builtins);
}

static int	get_link_list_size(t_link_list *head)
{
	int			size;
	t_link_list	*curr;

	curr = head;
	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

char	**link_list_to_array(t_link_list **head)
{
	char		**res;
	int			size;
	int			i;
	t_link_list	*curr;

	size = get_link_list_size(curr);
	i = 0;
	if (!head || !*head)
		return (NULL);
	curr = *head;
	curr = get_last_value(curr);
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (ft_putstr_fd("calloc failed\n", 2), NULL);
	curr = *head;
	while (i < size)
	{
		res[i] = ft_strdup(curr->param);
		if (res[i] == NULL)
			return (ft_putstr_fd("strdup error\n", 2), ft_free_2d(res), NULL);
		curr = curr->next;
		i++;
	}
	return (res);
}
