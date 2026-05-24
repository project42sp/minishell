#include "../../includes/minishell.h"

int	check_builtin(t_envp_path *envps, t_tree *tree)
{
	char	*cmd;
	int		err;

	if (!tree || !tree->node)
		return (2);
	err = -1;
	cmd = ((char **)tree->node)[0];
	if (ft_strncmp(cmd, "env", 3) == 0)
		err = ft_env(envps->envp);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		err = ft_echo(envps->envp, ((char **)tree->node));
	return (err);
}
