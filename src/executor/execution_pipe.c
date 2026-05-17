#include "../../includes/minishell.h"

int	ft_wait(void)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	while(waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	return (exit_code);
}

int	pipe_exec(t_envp_path *envps, t_tree *tree, int oldfd)
{
	int		status_code;
	t_fd	*fd;

	if (!tree)
		return (1);
	fd = fd_create(oldfd);
	if (tree && tree->signal != CMD)
		if (pipe(fd->fd) == -1)
			return (1);
	if (tree && tree->signal <= HEREDOC)
	{
		fd->last = 1;
		status_code = base_exec(envps, tree, fd);
		tree = NULL;
	}
	if (tree && tree->signal == PIPE)
	{
		status_code = base_exec(envps, tree->left, fd);
		tree->left = NULL;
	}
	if (tree && tree->signal == PIPE && tree->right)
	{
		status_code = pipe_exec(envps, tree->right, fd->fd[0]);
		tree->right = NULL;
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
