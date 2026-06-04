/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:23:58 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 17:44:21 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tree_print(t_tree *tree, int level)
{
	if (!tree)
		return ;
	tree_print(tree->right, level + 1);
	if (tree && tree->node)
		printf("%*c%s\n", level * 5, ' ', ((char **)tree->node)[0]);
	else
		switch (tree->signal) {
			case INPUT: printf("%*c<\n", level * 5, ' '); break;
			case OUTPUT: printf("%*c>\n", level * 5, ' '); break;
			case APPEND: printf("%*c>>\n", level * 5, ' '); break;
			case HEREDOC: printf("%*c<<\n", level * 5, ' '); break;
			case PIPE: printf("%*c | \n", level * 5, ' '); break;
			default:
				printf(" ");
		}
	tree_print(tree->left, level + 1);
}

void	tree_print_extense(t_tree *tree)
{
	if (!tree)
		return ;
	tree_print_extense(tree->left);
	if (tree->node)
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
