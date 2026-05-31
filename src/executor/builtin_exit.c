#include "../../includes/minishell.h"

int	ft_exit(t_envp_path *envp, char **cmd)
{
	int	err;

	err = 0;
	if (!*cmd)
		return (1);
	if (cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (cmd[1])
		err = ft_atoi(cmd[1]);
	child_free(envp);
	ft_printf("exit\n");
	exit(err);
}
