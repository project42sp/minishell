/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 18:07:03 by buehara           #+#    #+#             */
/*   Updated: 2026/05/31 18:07:05 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envp	*find_envp(t_envp **envp, char *key)
{
	t_envp	*temp;

	if (!envp || !key)
		return (NULL);
	temp = *envp;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_envp	*find_prev_envp(t_envp **envp, char *key)
{
	t_envp	*temp;

	if (!envp || !key)
		return (NULL);
	temp = *envp;
	if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		return (temp);
	while (temp && temp->next)
	{
		if (ft_strncmp(temp->next->key, key, ft_strlen(key)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_envp	*envp_index(t_envp **envp, int count)
{
	t_envp	*temp;
	int		index;

	if (!*envp || !count)
		return (NULL);
	index = 0;
	temp = *envp;
	while (index < count)
	{
		temp = temp->next;
		index++;
	}
	return (temp);
}

void	free_node(t_envp *envp)
{
	free(envp->key);
	free(envp->value);
	free(envp);
}

int	ft_unset(t_envp **envp, char **cmd)
{
	t_envp	*temp;
	t_envp	*prev;
	char	*key;

	if (!envp || !cmd || !cmd[1])
		return (1);
	key = cmd[1];
	temp = find_envp(envp, key);
	if (!temp)
		return (1);
	prev = find_prev_envp(envp, key);
	if (!temp || prev == temp)
		*envp = temp->next;
	else if (prev)
		prev->next = temp->next;
	free_node(temp);
	return (0);
}
