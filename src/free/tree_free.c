#include "../../includes/minishell.h"

void	tree_node_free(char **node)
{
	int	index;

	if (!node)
		return;
	index = 0;
	while (node[index] != NULL)
	{
		free(node[index]);
		index++;
	}
	node = NULL;
}

void	tree_free(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		tree_free(tree->left);
//	if (tree->node)
//		tree_node_free((char **)tree->node);
	if (tree->node)
		free(tree->node);
	if (tree->right)
		tree_free(tree->right);
	free(tree);
}
