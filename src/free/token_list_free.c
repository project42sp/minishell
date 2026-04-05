#include "../../includes/minishell.h"

void	token_list_free(t_token *head)
{
	t_token	*next;
	int		index;
	char	**temp;

	while (head)
	{
		next = head->next;
		if (head->token){
			temp = (char **)head->token;
			index = 0;
			while (temp && temp[index] != NULL)
			{
				free(temp[index]);
				index++;
			}
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
		free(head);
		head = next;
	}
}
