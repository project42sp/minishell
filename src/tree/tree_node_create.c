#include "../includes/minishell.h"

t_tree *tree_node_create(t_tree *left, t_token *token, t_tree *right)
{
	t_tree	*tree;

	if (!token)
		return (NULL);
	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->left = left;
	tree->signal = token->signal;
	tree->node = token->token;
	tree->right = right;
	return (tree);
}


