#include "../../includes/minishell.h"

int	base_redir(t_tree *tree, int *fd)
{
	if (!tree)
		return(1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (1);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

static int	define_stdin(t_tree *tree, int *fd, int permission)
{
	int	in_fd;

	if (!tree)
		return (1);
	if (tree->signal == INPUT || tree->signal == HEREDOC)
	{
		in_fd = open(((char **)tree->left->node)[0], permission);
		if (in_fd == -1)
			return (1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (1);
		close(in_fd);
	}
	else
		base_redir(tree, fd);
	return (0);
}

static int	define_stdout(t_tree *tree, int *fd, int permission)
{
	int	out_fd;

	if (!tree)
		return (1);
	if (tree->signal == OUTPUT || tree->signal == APPEND)
	{
		out_fd = open(((char **)tree->left->node)[0], permission, 0644);
		if (out_fd == -1)
			return (1);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (1);
		close(out_fd);
	}
	else
		base_redir(tree, fd);
	return (0);
}

static int	check_permission(t_tree *tree)
{
	int	permission;

	if (!tree)
		return (-1);
	if (tree->signal == OUTPUT)
		permission = O_WRONLY;
	else if (tree->signal == INPUT || tree->signal == HEREDOC)
		permission = O_RDONLY;
	else
		permission = O_WRONLY | O_APPEND;
	return (permission);
}

int	redirect(t_tree **tree, int *fd)
{
	int	permission;

	if (!*tree)
		return (1);
	if ((*tree)->signal >= INPUT && (*tree)->signal <= HEREDOC)
	{
		permission = check_permission(*tree);
		if (define_stdin((*tree), fd, permission))
			return (1);
		if (define_stdout((*tree), fd, permission))
			return (1);
		*tree = (*tree)->right;
	}
	else
		base_redir(*tree, fd);
	return (0);
}
