#include "../includes/minishell.h"

void	tree_print(t_tree *tree, int level)
{
	if (!tree)
		return ;
	tree_print(tree->right, level + 1);
	if (tree->node)
		printf("%*c[%s]\n", level * 4, ' ', (char *)tree->node);
	else
		printf("%*c[operator:%d]\n", level * 4, ' ', tree->signal);
	tree_print(tree->left, level + 1);
}

void	tree_print_extense(t_tree *tree)
{
	if (!tree)
		return ;
	tree_print_extense(tree->left);
	if (tree->node)
		ft_printf("%s ", (char *)tree->node);
	tree_print_extense(tree->right);
}
