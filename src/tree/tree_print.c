#include "../../includes/minishell.h"

void	tree_print(t_tree *tree, int level)
{
	if (!tree)
		return ;
	tree_print(tree->right, level + 1);
	printf("%*c%s\n", level * 5, ' ', ((char **)tree->node)[0]);
	tree_print(tree->left, level + 1);
}

void	tree_print_extense(t_tree *tree)
{
	if (!tree)
		return ;
	tree_print_extense(tree->left);
	ft_printf("%s \n", ((char **)tree->node)[0]);
	tree_print_extense(tree->right);
}
