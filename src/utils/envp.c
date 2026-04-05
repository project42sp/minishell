#include "../../includes/minishell.h"

static t_envp	*create_envp_node(char *envp)
{
	t_envp	*node;
	char	**temp;

	if (!envp)
		return (NULL);
	temp = ft_split(envp, '=');
	if (!temp)
		return (NULL);
	node = ft_calloc(sizeof(t_envp), 1);
	if (!node)
		return (NULL);
	node->key = temp[0];
	node->value = temp[1];
	node->next = NULL;
	free(temp);
	return (node);
}

static t_envp	*create_last_envp_node(char *envp, t_envp *list)
{
	t_envp	*head;

	if (!envp || !list)
		return (NULL);
	head = list;
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = create_envp_node(envp);
	if (!list)
	{
		envp_free(head);
		return (NULL);
	}
	return (head);
}

t_envp	*create_envp_table(char **envp)
{
	int		index;
	t_envp	*head;
	t_envp	*list;

	head = NULL;
	index = 0;
	list = create_envp_node(envp[index++]);
	if (!list)
		return (NULL);
	while (envp[index])
	{
		head = create_last_envp_node(envp[index], list);
		if (!head)
			return (NULL);
		index++;
	}
	return (head);
}
