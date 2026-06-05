/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:21:43 by buehara           #+#    #+#             */
/*   Updated: 2026/06/05 04:52:20 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	err_define_std(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	return (1);
}

static int	define_stdin(t_tree *tree, t_fd *fd, int permission)
{
	int		in_fd;

	if (!tree)
		return (1);
	if (tree->signal == INPUT || tree->signal == HEREDOC)
	{
		in_fd = open(((char **)tree->left->node)[0], permission);
		if (in_fd == -1)
			return (err_define_std(((char **)tree->left->node)[0]));
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (1);
		if (tree->signal == HEREDOC)
			unlink(((char **)tree->left->node)[0]);
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
	int		out_fd;
	char	*filename;

	if (!tree)
		return (1);
	if (tree->signal == OUTPUT || tree->signal == APPEND)
	{
		filename = ((char **)tree->left->node)[0];
		out_fd = open(filename, permission, 0644);
		if (out_fd == -1)
			return (err_define_std(filename));
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
	int	err;

	if (!*tree || (*tree)->signal == CMD)
		return (0);
	if (check_redir_files(*tree))
		return (1);
	err = 0;
	if (fd)
	{
		permission = check_permission(*tree);
		err = define_stdin((*tree), fd, permission);
		if (!err)
			err = define_stdout((*tree), fd, permission);
		if (err)
			return (1);
		*tree = (*tree)->right;
		err = redirect(tree, fd);
	}
	return (err);
}
