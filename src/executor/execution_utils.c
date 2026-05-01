# include "../../includes/minishell.h"

char	**create_path_table(t_envp *envp)
{
	char	**table;

	table = NULL;
	while (envp != NULL)
	{
		if (ft_strncmp(envp->key, "PATH", 4) == 0)
		{
			table = ft_split(envp->value, ':');
			break ;
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
			break ;
		free(full_path);
		full_path = NULL;
		index++;
	}
	return (full_path);
}

char	*find_path(char **path_envp, char **cmd)
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
