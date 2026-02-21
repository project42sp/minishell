/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:14:24 by thfernan          #+#    #+#             */
/*   Updated: 2026/02/21 16:22:57 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_tree(t_tree *root)
{
	t_command_node	*node;
	int				status;

	if (!root)
		return (0);
	node = (t_command_node *)root->node;
	expand_tree(root);
	if (node->type == NODE_COMMAND)
		status = exec_command(node);
	else if (node-> == NODE_PIPE)
		status = exec_pipe(root->left, root->right);
	else if (node->type == NODE_AND)
	{
		status = exec_tree(root->left);
		// if fale
		if (status != 0)
			status = exec_tree(root->right);
	}
	return (status);
}
