#include "../../includes/minishell.h"

void	ft_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd3);
	if (fd4 > -1)
		close(fd4);
}

static int	child_process(t_tree *tree, char **envp, t_fd *fd, char **path)
{
	char	*full_path;
	char	**node;

	node = (char **)tree->node;
	full_path = find_path(path, node);
	if (!full_path)
	{
		if (fd)
			free(fd);
		free(full_path);
		envp_char_free(&envp);
		perror("Error");
		exit(1); //ERROR PATH NOT FOUND
	}
	execve(full_path, node, envp);
	if (fd)
		free(fd);
	free(full_path);
	envp_char_free(&envp);
	perror("Error");
	exit(127);
}

static t_fd	*fd_create(int old_fd)
{
	t_fd	*fd;

	fd = ft_calloc(1, sizeof(t_fd));
	if (!fd)
		return (NULL);
	fd->fd[0] = -1;
	fd->fd[1] = -1;
	fd->oldfd = old_fd;
	fd->last = 0;
	return (fd);
}

static int	base_exec(char **path_table, t_tree *tree, char **envp, t_fd *fd)
{
	int		err;
	pid_t	pid;

	//if (builtin)
		//Run builtin
		// Return status code
	err = 0;
	pid = fork();
	if (pid == 0)
	{
		if (redirect(&tree, fd))
			exit(1); //EDIT RETURN ERROR FOR REDIR
		if (fd)
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
		err = child_process(tree, envp, fd, path_table);
	}
	if (fd)
		ft_close(fd->fd[1], fd->oldfd, -1, -1);
	tree_free(&tree);
	return (err);
}

static int	ft_wait(void)
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

static int	pipe_exec(char **path_table, t_tree *tree, char **envp, int oldfd)
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
		status_code = base_exec(path_table, tree, envp, fd);
		tree = NULL;
	}
	if (tree && tree->signal == PIPE)
	{
		status_code = base_exec(path_table, tree->left, envp, fd);
		tree->left = NULL;
	}
	if (tree && tree->signal == PIPE && tree->right)
	{
		status_code = pipe_exec(path_table, tree->right, envp, fd->fd[0]);
		tree->right = NULL;
	}
	else if (tree && tree->right)
	{
		fd->last = 1;
		status_code = base_exec(path_table, tree->right, envp, fd);
		tree->right = NULL;
	}
	ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
	free(fd);
	return (status_code);
}

int	execution(t_tree *tree, t_envp *envp_table)
{
	char	**path_table;
	int		status_code;
	char	**rebuilt_envp;

	if (!tree || !envp_table)
		return (1);
	status_code = 0;
	path_table = create_path_table(envp_table);
	if (!path_table)
		return (1);
	rebuilt_envp = envp_rebuilt(envp_table);
	if (!rebuilt_envp)
	{
		split_free(path_table);
		return (1);
	}
	if (tree->signal != CMD)
		status_code = pipe_exec(path_table, tree, rebuilt_envp, -1);
	else
		status_code = base_exec(path_table, tree, rebuilt_envp, NULL);
	status_code = ft_wait();
	split_free(rebuilt_envp);
	split_free(path_table);
	return (status_code);
}
