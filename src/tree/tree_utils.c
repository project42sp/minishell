# include "../includes/minishell.h"

t_token	*get_next_token(t_token *token)
{
	if (!token)
		return NULL;
	if (token->next != NULL)
		return token->next;
	return token;
}