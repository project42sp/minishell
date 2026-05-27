#include "../../includes/minishell.h"

int	count_keys(t_envp **envp)
{
	int	count;

	if (!envp)
		return (0);
	count = 0;
	while (envp[count])
	{
		count++;
	}
	return (count);
}

t_envp	**create_list(t_envp *envp)
{
	int		size;
	int		index;
	t_envp	**list;
	t_envp	*temp;

	if (!envp)
		return (NULL);
	size = envp_len(envp);
	list = (t_envp **)ft_calloc(sizeof(t_envp *), size + 1);
	if (!list)
		return (NULL);
	temp = envp;
	index = 0;
	while (index < size)
	{
		list[index] = temp;
		temp = temp->next;
		index++;
	}
	return (list);
}

t_envp	**envp_reorder(t_envp **envp)
{
	int		size;
	int		inner;
	int		out;
	t_envp	*key;

	if (!envp)
		return (NULL);
	size = count_keys(envp);
	out = 1;
	while (out < size)
	{
		inner = out - 1;
		key = envp[out];
		while (inner >= 0 &&
			ft_strncmp(envp[inner]->key, key->key, ft_strlen(envp[inner]->key)) > 0)
		{
			envp[inner + 1] = envp[inner];
			inner--;
		}
		envp[inner + 1] = key;
		out++;
	}
	return (envp);
}

void	print_export(t_envp **envp)
{
	int	index;

	index = 0;
	while(envp[index])
	{
		printf("declare\t-x ");
		printf("%s=", envp[index]->key);
		printf("\"%s\"\n", envp[index]->value);
		index++;
	}
}
