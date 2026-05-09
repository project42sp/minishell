#include "../../includes/minishell.h"

t_tree	*parser(char *input)
{
	t_check			flags;
	t_token			*tokens;
	t_tree			*tree;

	ft_bzero(&flags, sizeof(t_check));
	tokens = lexer(input, &flags);
	if (!tokens)
	{
		ft_printf("Lexer error: invalid syntax\n");
		return (NULL);
	}
	if (!validate_syntax(tokens))
	{
		token_list_free(tokens);
		return (NULL);
	}
	debug_lexer(tokens);
	tree = tree_create(tokens, &flags);
	token_list_free(tokens);
	return (tree);
}
