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

static char	*find_path(char **path_envp, char **cmd)
{
	char	*path;
	int		index;
	char	*full_path;

	path = ft_strjoin("/", cmd[0]);
	if (!path)
		return (NULL);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	index = 0;
	while(path_envp[index] != NULL)
	{
		full_path = ft_strjoin(path_envp[index], path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		index++;
	}
	return (NULL);
}


static int	child_process(char **envp, char **cmd, char *path)
{
	execve(path, cmd, envp);
	free(path);
	// free cmd
	envp_char_free(&envp);
	perror("Error");
	exit(127);
}

static int	base_exec(char **envp, t_tree *tree)
{
	char	*path;
	int		err;
	char	**node;

	//if (builtin)
		//Run builtin
		// Return status code
	err = 0;
	path = NULL;
	node = (char **)tree->node;
	path = find_path(envp, node);
	if (!path)
		return (1);
	err = child_process(envp, node, path);
	free(path);
	return (err);
}

int execution(t_tree *tree, t_envp *envp)
{
	char	**path_table;
	int		status_code;
	pid_t	pid;
	int		fd[2];

	status_code = 0;
	path_table = create_path_table(envp);
	if (!path_table)
		return (1);
	if (tree->signal != CMD && pipe(fd) == -1)
	{
		envp_char_free(&path_table);
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (tree->signal != CMD && redirect(&tree, fd))
			return (1);
		status_code = base_exec(path_table, tree);
	}
	if (tree->signal != CMD)
	{
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, &status_code, 0);
	envp_char_free(&path_table);
	return (status_code); // Temp to make the function compile
	//TODO: Criar o export e adicionar o status_code dentro da variavel $?
}
