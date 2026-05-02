#include "../../includes/minishell.h"

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
