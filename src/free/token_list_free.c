#include "../includes/minishell.h"

void	token_list_free(t_token *head)
{
	t_token *next;

	while (head)
	{
		next = head->next;
		// Free no que a ft_strdup do token_node alocou
		free(head->token);
		free(head);
		head = next;
	}
}