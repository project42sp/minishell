#include "../../includes/minishell.h"

int	envp_len(t_envp *head)
{
	size_t	len;
	t_envp	*temp;

	if (!head)
		return (0);
	len = 0;
	temp = head;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

char	*envp_rebuilt_util(t_envp *node)
{
	char	*temp;
	char	*full_str;

	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (NULL);
	full_str = ft_strjoin(temp, node->value);
	if (!full_str)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (full_str);
}

char	**envp_rebuilt(t_envp *head)
{
	char	**envp;
	char	*temp;
	size_t	len;
	size_t	index;

	if (!head)
		return (NULL);
	len = envp_len(head);
	envp = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!envp)
		return (NULL);
	index = 0;
	while (head)
	{
		temp = envp_rebuilt_util(head);
		if (!temp)
		{
			envp_char_free(&envp);
			return (NULL);
		}
		envp[index] = temp;
		temp = NULL;
		index++;
	}
	return (envp);
}
