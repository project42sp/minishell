#include "../../includes/minishell.h"

t_tree	*parser(char *input)
{
	char 			***tokens;
	t_tokens_type	*signals;
	t_check			flags;
	t_token			*head;
	t_tree			*tree;

	tokens = lexer(input, &signals, &flags);
	if (!tokens)
	{
		ft_printf("Lexer error: invalid syntax\n");
		return (NULL);
	}
	head = token_create(tokens, signals);
	if (!head)
	{
		envp_char_free(tokens);
		free(signals);
		return (NULL);
	}
	tree = tree_create(head, &flags);
	token_list_free(head);
	envp_char_free(tokens);
	free(signals);
	return (tree);
}
