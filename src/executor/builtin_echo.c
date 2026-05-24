#include "../../includes/minishell.h"

static void	ft_echo_print(char **envp, char **cmd, int flag)
{
	int count;

	(void)envp;
	count = 2;
	while(cmd[count - flag])
	{
		ft_printf("%s", cmd[count - flag]);
		count++;
		if (cmd[count - flag])
			write(1, &" ", 1);
	}
	if (flag)
		write(1, &"\n", 1);
}

int	ft_echo(char **envp, char **cmd)
{
	int i;
	int flag;

	(void)envp;
	if (!envp)
		return (2);
	i = 1;
	flag = 0;
	if ('-' == cmd[1][0])
	{
		while (cmd[1][i] && cmd[1][i] == 'n')
			i++;
		if ((int)(ft_strlen(cmd[1])) == i + 1)
			flag = 1;
	}
	ft_echo_print(envp, cmd, flag);
	return (0);
}
