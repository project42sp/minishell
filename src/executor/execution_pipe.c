/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:20:20 by buehara           #+#    #+#             */
/*   Updated: 2026/05/23 15:20:23 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_cmd_count(t_tree *tree)
{
	t_tree	*temp;
	int		count;

	if (!tree)
		return (0);
	temp = tree;
	count = 0;
	count += tree_cmd_count(temp->left);
	count += tree_cmd_count(temp->right);
	if (tree->signal == CMD)
		count++;
	return (count);
}

int	pipe_exec(t_envp_path *envps, t_tree *tree, int oldfd)
{
	int		status_code;
	t_fd	*fd;

	if (!tree)
		return (1);
	fd = fd_create(oldfd);
	if (!fd)
		return (1);
	if (tree && tree->signal != CMD)
		if (pipe(fd->fd) == -1)
		{
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
			free(fd);
			return (1);
		}
	if (tree && tree->signal <= HEREDOC)
	{
		fd->last = 1;
		status_code = base_exec(envps, tree, fd);
		tree = NULL;
	}
	if (tree && tree->signal == PIPE)
	{
		status_code = base_exec(envps, tree->left, fd);
		status_code = pipe_exec(envps, tree->right, fd->fd[0]);
		tree->left = NULL;
		tree->right = NULL;
		free(tree);
	}
	else if (tree && tree->right)
	{
		fd->last = 1;
		status_code = base_exec(envps, tree->right, fd);
		tree->right = NULL;
	}
	ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
	free(fd);
	return (status_code);
}
