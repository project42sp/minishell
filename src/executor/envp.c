/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:24:10 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:24:12 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envp	*create_last_envp_node(char *envp, t_envp *list)
{
	t_envp	*head;

	if (!envp || !list)
		return (NULL);
	head = list;
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = create_envp_node(envp);
	if (!list)
	{
		envp_free(&head);
		return (NULL);
	}
	return (head);
}

t_envp	*create_envp_table(char **envp)
{
	int		index;
	t_envp	*list;

	index = 0;
	list = create_envp_node(envp[index]);
	index++;
	if (!list)
		return (NULL);
	while (envp[index])
	{
		list = create_last_envp_node(envp[index], list);
		if (!list)
			return (NULL);
		index++;
	}
	return (list);
}
