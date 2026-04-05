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

static char	*find_path(char **path_envp, t_tree *tree)
{
	char	*path;
	int		index;
	char	*full_path;

	path = (char *)tree->node;
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
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		index++;
	}
	return (NULL);
}

static int	child_process(char **envp, t_tree *tree, char *path)
{
	execve(path, (char **)tree->node, envp);
	free(path);
	tree_free(tree);
	// Funcao free path_envp (char **)
	perror("Error: ");
	exit(127);
}

static int	base_exec(char **envp, t_tree *tree)
{
	char	*path;
	pid_t	pid;
	int		err;

	//if (builtin)
		//Run builtin
		// Return status code
	path = find_path(envp, tree);
	if (!path)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		err = child_process(envp, tree, path);
		return err;
	}
	else
	{
		perror("Error: ");
		//Return error for fork function
		return (127);
	}
}

int execution(t_tree *tree, t_envp *envp)
{
	char	**envp_table;
	int		status_error;

	envp_table = create_path_table(envp);
	if (!envp_table)
		return (1);
	if (tree->signal == CMD)
	{
		status_error = base_exec(envp_table, tree);
		return (status_error); // Temp to make the function compile
	}
	envp_char_free(envp_table);
	//TODO: Criar o export e adicionar o status_error dentro da variavel $?
	return (0);
}
