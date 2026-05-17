/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:21:43 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:21:47 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	define_stdin(t_tree *tree, t_fd *fd, int permission)
{
	int	in_fd;

	if (!tree)
		return (1);
	if (tree->signal == INPUT || tree->signal == HEREDOC)
	{
		in_fd = open(((char **)tree->left->node)[0], permission);
		if (in_fd == -1)
			return (1);
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (1);
		close(in_fd);
	}
	else if (fd && fd->oldfd > -1)
	{
		if (dup2(fd->oldfd, STDIN_FILENO) == -1)
			return (1);
	}
	else if (fd->last && tree->signal >= INPUT)
		if (dup2(fd->fd[0], STDIN_FILENO) == -1)
			return (1);
	return (0);
}

static int	define_stdout(t_tree *tree, t_fd *fd, int permission)
{
	int	out_fd;

	if (!tree)
		return (1);
	if (tree->signal == OUTPUT || tree->signal == APPEND)
	{
		out_fd = open(((char **)tree->left->node)[0], permission, 0644);
		if (out_fd == -1)
			return (1);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (1);
		close(out_fd);
	}
	else if (!fd->last)
	{
		if (dup2(fd->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

static int	check_permission(t_tree *tree)
{
	int	permission;

	if (!tree)
		return (-1);
	if (tree->signal == OUTPUT)
		permission = O_WRONLY | O_CREAT | O_TRUNC;
	else if (tree->signal == INPUT || tree->signal == HEREDOC)
		permission = O_RDONLY;
	else
		permission = O_WRONLY | O_APPEND | O_CREAT;
	return (permission);
}

int	redirect(t_tree **tree, t_fd *fd)
{
	int	permission;

	if (!*tree)
		return (1);
	permission = check_permission(*tree);
	if (fd)
	{
		if (define_stdin((*tree), fd, permission))
			return (1);
		if (define_stdout((*tree), fd, permission))
			return (1);
		ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
		if ((*tree)->signal >= INPUT && (*tree)->signal <= HEREDOC)
			*tree = (*tree)->right;
	}
	return (0);
}
