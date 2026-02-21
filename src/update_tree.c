/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:24:19 by thfernan          #+#    #+#             */
/*   Updated: 2026/02/21 16:28:36 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*update_tree(t_tree *current_tree, char *command_line)
{
	t_tree	*new_tree;

	if (current_tree)
		free_tree(current_tree);
	// parse or create???
	new_tree = parse_command(command_line);
	return(new_tree);
}
