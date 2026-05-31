#include "../../includes/minishell.h"

int	check_export_args(char *cmd)
{
	int	index;
	char *barr;

	if (!ft_isalpha(cmd[0]) && !(cmd[0] == '_'))
		return (1);
	index = 1;
	barr = ft_strchr(cmd, '\\');
	if (barr)
		ft_memmove(cmd, barr + 1, ft_strlen(barr) + 1);
	while(cmd[index])
	{
		if (cmd[index] == '\\' || cmd[index] == '#' || cmd[index] == '*' ||
			cmd[index] == ' ' || cmd[index] == '!' || cmd[index] == '@')
			return (1);
		index++;
	}
	return (0);
}

t_envp	*find_export_node(t_envp *envp, char *cmd)
{
	t_envp	*temp;

	if (!envp || !cmd)
		return (NULL);
	temp = envp;
	while (temp)
	{
		if (ft_strncmp(temp->key, cmd, ft_strlen(temp->key)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	append_env_node(t_envp **envp, char *cmd, t_envp *find)
{
	char	*index;
	char	*new_value;

	new_value = NULL;
	if (!find)
	{
		*envp = create_last_envp_node(cmd, *envp);
		return ;
	}
	index = ft_strchr(cmd, '=');
	if (index && index[1])
	{
		new_value = ft_strdup(index + 1);
		free(find->value);
		find->value = new_value;
	}
}

int	export_args(t_envp **envp, char **cmd)
{
	int		err;
	int		index;
	t_envp	*find;

	index = 1;
	err = 0;
	(void)envp;
	while(cmd[index])
	{
		if(check_export_args(cmd[index]))
			err = 1;
		if (err)
			continue ;
		find = find_export_node(*envp, cmd[index]);
		append_env_node(envp, cmd[index], find);
		index++;
	}
	return (err);
}

int	ft_export(t_envp **envp, char **cmd)
{
	int		err;

	if (!cmd || !envp)
		return (1);
	err = 0;
	if (!cmd[1])
		err = export_empty(envp);
	else
		err = export_args(envp, cmd);
	return (err);
}
