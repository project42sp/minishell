/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 18:06:53 by buehara           #+#    #+#             */
/*   Updated: 2026/05/31 18:06:54 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_export_args(char *cmd)
{
	int		index;
	char	*barr;

	if (!ft_isalpha(cmd[0]) && !(cmd[0] == '_'))
		return (1);
	index = 1;
	barr = ft_strchr(cmd, '\\');
	if (barr)
		ft_memmove(barr, barr + 1, ft_strlen(barr));
	while (cmd[index])
	{
		if (cmd[index] == '\\' || cmd[index] == '#' || cmd[index] == '*'
			|| cmd[index] == ' ' || cmd[index] == '!' || cmd[index] == '@')
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
	if (index)
	{
		new_value = ft_strdup(&index[1]);
		if (!new_value)
			return ;
		free(find->value);
		if (!index[1])
			bzero(new_value, 1);
		find->value = new_value;
		find->flag = ENV;
	}
}

int	export_args(t_envp **envp, char **cmd)
{
	int		err;
	int		index;
	t_envp	*find;

	index = 1;
	err = 0;
	while (cmd[index])
	{
		if (check_export_args(cmd[index]))
		{
			err = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[index], 2);
			ft_putendl_fd("': not a valid indentifier", 2);
			index++;
			continue ;
		}
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
