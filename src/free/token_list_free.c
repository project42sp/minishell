#include "../../includes/minishell.h"

void	token_list_free(t_token *head)
{
	t_token	*next;
	char	**temp;

	while (head)
	{
		next = head->next;
		if (head->token)
		{
			temp = (char **)head->token;
			if (temp[0])
				free(temp[0]);
			free(temp);
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
