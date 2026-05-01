#include "../../includes/minishell.h"

static char	**create_path_table(t_envp *envp)
{
	char	**table;

	table = NULL;
	while(envp != NULL)
	{
		if (ft_strncmp(envp->key, "PATH", 4) == 0)
		{
			table = ft_split(envp->value, ':');
			break;
		}
		envp = envp->next;
	}
	return (table);
}

static char	*find_fullpath(char *path, char **path_envp)
{
	int		index;
	char	*full_path;

	index = 0;
	full_path = NULL;
	while(path_envp[index] != NULL)
	{
		full_path = ft_strjoin(path_envp[index], path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			break;
		free(full_path);
		full_path = NULL;
		index++;
	}
	return (full_path);
}

static char	*find_path(char **path_envp, char **cmd)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin("/", cmd[0]);
	if (!path)
		return (NULL);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	full_path = find_fullpath(path, path_envp);
	free(path);
	return (full_path);
}


static int	child_process(t_tree *tree, char **envp, int fd[2], char **path)
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

static int	base_exec(char **path_table, t_tree *tree, char **envp)
{
	int		err;
	pid_t	pid;
	int		fd[2];

	//if (builtin)
		//Run builtin
		// Return status code
	err = 0;
	if (tree->signal != CMD)
		if (pipe(fd) == -1)
			return (1);
	pid = fork();
	if (pid == 0)
		err = child_process(tree, envp, fd, path_table);
	if (tree->signal != CMD)
	{
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, &err, 0);
	return (err);
}

int execution(t_tree *tree, t_envp *envp_table)
{
	char	**path_table;
	int		status_code;
	char	**rebuilt_envp;

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
	status_code = base_exec(path_table, tree, rebuilt_envp);
	split_free(rebuilt_envp);
	split_free(path_table);
	return (status_code);
	//TODO: Criar o export e adicionar o status_code dentro da variavel $?
}
