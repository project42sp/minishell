#include "../includes/minishell.h"

void	token_list_free(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head->token);
		free(head);
		head = next;
	}
}
