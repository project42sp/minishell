#include "../includes/minishell.h"

static t_tree *tree_node_create(t_tree *left, void *token, t_tree *right)
{
	t_tree	*tree;

	if (!token)
		return (NULL);
	tree = (t_tree *)calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->left = left;
	tree->node = token;
	tree->right = right;
	return (tree);
}

