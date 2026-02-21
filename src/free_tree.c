/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:39:11 by thfernan          #+#    #+#             */
/*   Updated: 2026/02/21 16:41:57 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tree(t_tree *ast)
{
	if (!ast)
		return ;
	free_tree(ast->left);
	free_tree(ast->right);
	if (ast->node)
		free(ast->node);
	free(ast);
}
