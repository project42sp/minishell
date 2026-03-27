#include "../includes/minishell.h"

void	tree_free(t_tree *tree)
{
	if (!tree)
		return ;
	tree_free(tree->left);
	tree_free(tree->right);
	free(tree);
	// Não libera tree->node, já foi liberado na token_list_free, mesmo ponteiro
}