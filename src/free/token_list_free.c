#include "../../includes/minishell.h"

void	token_list_free(t_token *head)
{
	t_token	*next;
	int		index;
	char	**temp;

	while (head)
	{
		next = head->next;
		temp = (char **)head->token;
		index = 0;
		while (temp && temp[index] != NULL)
		{
			free(temp[index]);
			index++;
		}
		//free(head->token);
		free(head);
		head = next;
	}
}
