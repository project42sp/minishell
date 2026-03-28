/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:44:48 by buehara           #+#    #+#             */
/*   Updated: 2026/03/21 21:40:23 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	tree_print(t_tree *tree, int level)
{
	if (!tree)
		return ;
	tree_print(tree->right, level + 1);
	printf("%*c%s\n", level * 5, ' ', (char *)tree->node);
	tree_print(tree->left, level + 1);
}

void	tree_print_extense(t_tree *tree)
{
	if (!tree)
		return ;
	tree_print_extense(tree->left);
	ft_printf("%s ", (char *)tree->node);
	tree_print_extense(tree->right);
}
