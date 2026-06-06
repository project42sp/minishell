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

static char	**ft_double_realloc(void *list_void, void *append_void)
{
	int		index;
	char	**new_list;
	char	**list;
	char	**append;

	index = 0;
	list = (char **)list_void;
	append = ((char **)append_void);
	while(list[index])
		index++;
	new_list = ft_calloc(sizeof(char *), index + 2);
	if (!new_list)
		return (NULL);
	index = 0;
	while(list[index] != NULL)
	{
		new_list[index] = list[index];
		index++;
	}
	new_list[index++] = append[0];
	new_list[index] = NULL;
	free(list);
	free(append);
	return (new_list);
}

t_token	*token_cmd_reorder(t_token *token)
{
	t_token	*head;
	t_token	*temp;
	t_token	*ref;
	char	**list;

	ref = token;
	while (token && token->signal != EOFILE)
	{
		head = token;
		while (token && token->signal == CMD)
		{
			token = token->next;
			if (token && token->signal == CMD)
			{
				list = ft_double_realloc(head->token, token->token);
				head->token = (void *)list;
				temp = token;
				head->next = token->next;
				token = token->next;
				free(temp);
			}
		}
		token = token->next;
	}
	return (ref);
}

t_token	*token_node(char *token_str, t_tokens_type signal)
{
	t_token	*node;
	char	**arr;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->signal = signal;
	if (token_str)
	{
		arr = ft_calloc(2, sizeof(char *));
		if (!arr)
		{
			free(node);
			return (NULL);
		}
		arr[0] = token_str;
		arr[1] = NULL;
		node->token = arr;
	}
	else
		node->token = NULL;
	node->next = NULL;
	return (node);
}
