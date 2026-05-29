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
		if (ft_strncmp(temp->key, cmd, ft_strlen(temp->key)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	append_env_node(t_envp **envp, char *cmd, t_envp *find)
{
	if (!find)
		//Atualizar funcao de criar nodo de envp para gerar nodo
		// sem valor, sem quebrar
		// Pois o export pode criar nodos sem valores
		// e estes terao a flag EXPORT
		// se o export tiver um '='
		// então a flag será ENV
		// mas também não terá value se não tiver string depois do '='
		// Criar também função para atualizar o nodo caso
		// a key já exista no env
}

int	export_args(t_envp **envp, char **cmd)
{
	int		err;
	int		index;
	t_envp	*find;

	index = 1;
	(void)envp;
	while(cmd[index])
	{
		if(check_export_args(cmd[index]))
			err = 1;
		if (err)
			continue ;
		find = find_export_node(*envp, cmd[index]);
		append_env_node(envp, cmd[index], find);
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
