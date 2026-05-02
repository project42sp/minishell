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

	if (tree->signal != CMD)
	{
		if (redirect(&tree, fd))
			return (1);
	}
	node = (char **)tree->node;
	full_path = find_path(path, node);
	execve(full_path, node, envp);
	free(full_path);
	envp_char_free(&envp);
	perror("Error");
	exit(127);
}

static void	fd_init(t_fd *fd)
{
	fd->fd[0] = -1;
	fd->fd[1] = -1;
	fd->oldfd = -1;
}

static int	base_exec(char **path_table, t_tree *tree, char **envp)
{
	int		err;
	pid_t	pid;
	t_fd	*fd;

	//if (builtin)
		//Run builtin
		// Return status code
	err = 0;
	fd = ft_calloc(1, sizeof(t_fd));
	if (!fd)
		return (1);
	fd_init(fd);
	if (tree->signal != CMD)
		if (pipe(fd->fd) == -1)
			return (1);
	pid = fork();
	if (pid == 0)
		err = child_process(tree, envp, fd, path_table);
	if (tree->signal != CMD)
		ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
	waitpid(pid, &err, 0);
	free(fd);
	return (err);
}

static int	pipe_exec(char **path_table, t_tree *tree, char **envp, int oldfd)
{
	int	status_code;

	if (!tree)
		return (1);
	if (tree->left && tree->signal == PIPE)
		status_code = pipe_exec(path_table, tree->left, envp, oldfd);
	if (tree->right && tree->signal == PIPE)
		status_code = pipe_exec(path_table, tree->right, envp, oldfd);
	if (tree->signal <= PIPE)
		status_code = base_exec(path_table, tree, envp);
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
	if (tree->signal != PIPE)
		status_code = base_exec(path_table, tree, rebuilt_envp);
	else
		status_code = pipe_exec(path_table, tree, rebuilt_envp, -1);
	split_free(rebuilt_envp);
	split_free(path_table);
	return (status_code);
	//TODO: Criar o export e adicionar o status_code dentro da variavel $?
}
