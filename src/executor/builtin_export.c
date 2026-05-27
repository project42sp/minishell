#include "../../includes/minishell.h"

int	ft_export(t_envp **envp, char **cmd)
{
	t_envp	**list;

	if (!cmd)
		return (1);
	if (!cmd[1])
	{
		list = create_list(*envp);
		list = envp_reorder(list);
		print_export(list);
		free(list);
	}
	return (0);
}
