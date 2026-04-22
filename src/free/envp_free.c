#include "../../includes/minishell.h"

void	envp_free(t_envp **envp)
{
	t_envp	*tmp;
	t_envp	*current;

	if (!envp ||!*envp)
		return ;
	current = *envp;
	while (current)
	{
		tmp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
	*envp = NULL;
}

void	split_free(char **split)
{
	size_t	index;

	if (!split)
		return ;
	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
	split = NULL;
}

void	envp_char_free(char ***envp)
{
	size_t	index;

	if (!envp || !*envp)
		return ;
	index = 0;
	while((*envp)[index])
	{
		split_free(&(*envp)[index]);
		(*envp)[index] = NULL;
		index++;
	}
	free(envp);
	envp = NULL;
}
