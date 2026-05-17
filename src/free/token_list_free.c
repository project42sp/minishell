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
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->token)
		{
			free(((char **)temp->token)[0]);
			free(temp->token);
		}
		free(temp);
	}
}

void	token_free_partial(t_token *head, t_token *limit)
{
	t_token *temp;
	t_token *current;

	current = head;
	while (current && current != limit)
	{
		temp = current;
		current = current->next;
		free(temp->token);
		free(temp);
	}
}