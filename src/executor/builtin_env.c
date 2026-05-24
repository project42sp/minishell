#include "../../includes/minishell.h"

int	ft_env(char **envp)
{
	int	index;

	index = 0;
	while(envp[index])
	{
		ft_printf("%s\n", envp[index]);
		index++;
	}
	return (0);
}
