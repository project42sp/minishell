/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 18:07:16 by buehara           #+#    #+#             */
/*   Updated: 2026/05/31 18:07:19 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_envp	*fill_envp_node(char *key, char *value, t_export flag)
{
	t_envp	*node;

	node = ft_calloc(sizeof(t_envp), 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->flag = flag;
	node->next = NULL;
	return (node);
}

static char	*divider_for_key(char *envp)
{
	char	*divider;
	char	*key;

	if (!envp)
		return (NULL);
	divider = ft_strchr(envp, '=');
	if (!divider)
	{
		key = ft_strdup(envp);
		if (!key)
			return (NULL);
		return (key);
	}
	key = ft_substr(envp, 0, divider - envp);
	if (!key)
		return (NULL);
	return (key);
}

static char	*divider_for_value(char *envp)
{
	char	*value;
	char	*divider;

	if (!envp)
		return (NULL);
	divider = ft_strchr(envp, '=');
	if (!divider)
		return (NULL);
	if (!divider[1])
		return (NULL);
	value = ft_strdup(&divider[1]);
	if (!value)
		return (NULL);
	return (value);
}

static t_export	divider_for_flag(char *envp)
{
	char		*divider;
	t_export	flag;

	if (!envp)
		return (0);
	divider = ft_strchr(envp, '=');
	if (!divider)
		flag = EXPORT;
	else
		flag = ENV;
	return (flag);
}

t_envp	*create_envp_node(char *envp)
{
	t_envp		*node;
	char		*key;
	char		*value;
	t_export	flag;

	if (!envp)
		return (NULL);
	key = divider_for_key(envp);
	if (!key)
		return (NULL);
	value = divider_for_value(envp);
	flag = divider_for_flag(envp);
	node = fill_envp_node(key, value, flag);
	if (!node)
	{
		free(key);
		if (value)
			free(value);
		return (NULL);
	}
	return (node);
}
