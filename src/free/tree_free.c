/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:23:30 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:23:32 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	tree_free(t_tree **tree)
{
	if (!tree || !*tree)
		return ;
	if (*tree && (*tree)->left != NULL)
	{
		tree_free(&((*tree)->left));
		(*tree)->left = NULL;
	}
	if (*tree && (*tree)->node)
	{
		split_free((char **)(*tree)->node);
		(*tree)->node = NULL;
	}
	if (*tree && (*tree)->right != NULL)
	{
		tree_free(&((*tree)->right));
		(*tree)->right = NULL;
	}
	free(*tree);
	*tree = NULL;
}
