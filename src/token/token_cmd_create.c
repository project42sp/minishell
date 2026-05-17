/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:22:09 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:22:14 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*token_node(char **token, t_tokens_type signal)
{
	t_token	*node;

	node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->signal = signal;
	node->token = token;
	node->next = NULL;
	return (node);
}

t_token	*token_create(char ***tokens, t_tokens_type *signal)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;
	int		index;

	if (!tokens || !signal)
		return (NULL);
	head = NULL;
	prev = NULL;
	index = 0;
	while (signal[index] != EOFILE)
	{
		current = token_node(tokens[index], signal[index]);
		if (!current)
		{
			token_list_free(head);
			return (NULL);
		}
		if (!head)
			head = current;
		else
			prev->next = current;
		prev = current;
		tokens[index] = NULL;
		index++;
	}
	return (head);
}
