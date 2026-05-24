/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 02:41:37 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 02:41:39 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pid	*pid_create_free(t_tree *tree, t_envp_path *envp)
{
	t_pid	*pid;

	if (!tree || !envp)
		return (NULL);
	pid = create_pid(tree);
	if (!pid)
	{
		tree_free(&tree);
		envp_path_free(&envp);
		return (NULL);
	}
	return (pid);
}

void	pid_free(t_pid **pid)
{
	if (!*pid)
		return ;
	if ((*pid)->pid)
		free((*pid)->pid);
	free(*pid);
}

t_pid	*create_pid(t_tree *tree)
{
	t_pid	*pid;

	if (!tree)
		return (NULL);
	pid = ft_calloc(sizeof(t_pid), 1);
	if (!pid)
		return (NULL);
	pid->size = tree_cmd_count(tree);
	if (!pid->size)
	{
		free(pid);
		return (NULL);
	}
	pid->pid = ft_calloc(sizeof(pid_t), pid->size + 1);
	if (!pid->pid)
	{
		free(pid);
		return (NULL);
	}
	pid->index = 0;
	return (pid);
}
