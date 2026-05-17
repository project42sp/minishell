/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:23:22 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:23:24 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_list_free(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->token)
		{
			split_free((char **)head->token);
			free(head->token);
		}
		free(head);
		head = next;
	}
}

void	token_no_content_free(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->token)
		{
			free(((char **)head->token)[0]);
			free(head->token);
		}
		free(head);
		head = next;
	}
}
