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
			return (1);
		err = child_process(tree, envp, fd, path_table);
	}
	ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
	waitpid(pid, &err, 0);
	return (err);
}

static int	pipe_exec(char **path_table, t_tree *tree, char **envp, int oldfd)
{
	int		status_code;
	t_fd	*fd;

	//TODO:"OLDFD needs to reach stdin and stdout for this to work.
	// The child needs to inherit the fds and connect the pipes accordingly.
	// This setup needs to be reviewed because, right now it just doesn't makes sense
	// in the way it's been built..."
	if (!tree)
		return (1);
	fd = fd_create(oldfd);
	if (pipe(fd->fd) == -1)
		return (1);
	if (tree->signal == PIPE)
		status_code = base_exec(path_table, tree->left, envp, fd->fd[1]);
	if (tree->right && tree->signal == PIPE)
		status_code = pipe_exec(path_table, tree->right, envp, fd->oldfd);
	else if (tree->right)
	{
		fd->last = 1;
		status_code = base_exec(path_table, tree->right, envp, fd->oldfd);
	}
	return (status_code);
}

int	execution(t_tree *tree, t_envp *envp_table)
{
	char	**path_table;
	int		status_code;
	char	**rebuilt_envp;
	t_fd	*fd;

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
	if (tree->signal == PIPE)
	{
		fd = fd_create(-1);
		if (!fd)
			return (1);
		status_code = pipe_exec(path_table, tree, rebuilt_envp, fd);
	}
	else
		status_code = base_exec(path_table, tree, rebuilt_envp, NULL);
	split_free(rebuilt_envp);
	split_free(path_table);
	return (status_code);
	//TODO: Criar o export e adicionar o status_code dentro da variavel $?
}
