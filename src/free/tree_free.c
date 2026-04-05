#include "../../includes/minishell.h"

void	tree_free(t_tree *tree)
{
	if (!tree)
		return ;
	tree_free(tree->left);
	free(tree->node);
	tree_free(tree->right);
	free(tree);
}
