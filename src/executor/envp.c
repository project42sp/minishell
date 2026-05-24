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

static t_envp	*fill_envp_node(char *key, char *value)
{
	t_envp	*node;

	node = ft_calloc(sizeof(t_envp), 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

static t_envp	*create_envp_node(char *envp)
{
	t_envp	*node;
	char	*divider;
	char	*key;
	char	*value;

	if (!envp)
		return (NULL);
	divider = ft_strchr(envp, '=');
	key = ft_substr(envp, 0, divider - envp);
	if (!key)
		return (NULL);
	value = ft_strdup(divider + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	node = fill_envp_node(key, value);
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	return (node);
}

static t_envp	*create_last_envp_node(char *envp, t_envp *list)
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
