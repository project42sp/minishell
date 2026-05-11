#include "../../includes/minishell.h"

t_token	*get_next_token(t_token *token)
{
	if (!token)
		return (NULL);
	if (token->next != NULL)
		return (token->next);
	return (token);
}

t_tree	*create_cmd_node(char **argv)
{
	t_tree	*node;
	t_token	temp_token;
	t_token	*token_ptr;

	temp_token.signal = CMD;
	temp_token.token = argv;
	temp_token.next = NULL;
	token_ptr = &temp_token;
	node = tree_node_create(NULL, &token_ptr, NULL);
	return (node);
}
