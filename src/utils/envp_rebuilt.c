/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_rebuilt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:24:20 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:24:22 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	envp_len(t_envp *head)
{
	size_t	len;
	t_envp	*temp;

	if (!head)
		return (0);
	len = 0;
	temp = head;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

char	*envp_join(t_envp *node)
{
	char	*temp;
	char	*full_str;

	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (NULL);
	full_str = ft_strjoin(temp, node->value);
	if (!full_str)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (full_str);
}

char	**envp_table_init(t_envp *head)
{
	char	**envp;
	size_t	len;

	if (!head)
		return (NULL);
	len = envp_len(head);
	envp = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	return (envp);
}

char	**envp_rebuilt(t_envp *head)
{
	char	**envp;
	char	*temp;
	size_t	index;
	t_envp	*envp_temp;

	envp = envp_table_init(head);
	if (!envp)
		return (NULL);
	index = 0;
	envp_temp = head;
	while (envp_temp != NULL)
	{
		temp = envp_join(envp_temp);
		if (!temp)
		{
			envp_char_free(&envp);
			return (NULL);
		}
		envp[index] = temp;
		temp = NULL;
		envp_temp = envp_temp->next;
		index++;
	}
	return (envp);
}
