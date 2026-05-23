/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:23:58 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:23:59 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	tokens_print(t_token *token)
{
	if (!token)
		return ;
	ft_printf("%s \n", ((char **)token->token)[0]);
	tokens_print(token->next);
}
