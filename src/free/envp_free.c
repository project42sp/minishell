#include "../../includes/minishell.h"

void	envp_free(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	envp_char_free(char **envp)
{
	size_t	index;

	index = 0;
	while(envp[index])
	{
		free(envp[index]);
		index++;
	}
	free(envp);
}
