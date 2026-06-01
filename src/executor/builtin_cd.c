/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:52:34 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 14:52:36 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_node_envp(t_envp_path *envps, char *key, char *path)
{
	t_envp	*temp;

	if (!envps || !path)
		return (1);
	temp = envps->envp_og;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			free(temp->value);
			temp->value = path;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

char	*get_current_pwd(void)
{
	char	*temp;
	char	*path;
	int		size;

	size = 4096;
	temp = NULL;
	temp = getcwd(temp, size);
	if (!temp)
		return (NULL);
	path = ft_strdup(temp);
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (path);
}

int	move_to_correct_dir(t_envp_path *envps, char **dirpwd)
{
	int		err;
	char	*home_path;
	t_envp	*node;

	if (!dirpwd)
		return (1);
	if (!dirpwd[1])
	{
		node = find_envp(&envps->envp_og, "HOME");
		home_path = node->value;
		if (!home_path)
		{
			ft_putstr_fd("cd: HOME not set", 2);
			return (1);
		}
		err = chdir(home_path);
		return (err);
	}
	err = chdir(dirpwd[1]);
	return (err);
}

int	cd_return_error(void)
{
	ft_putendl_fd("minishell: cd: too many arguments", 2);
	return (1);
}

int	ft_cd(t_envp_path *envps, char **dirpwd)
{
	int		err;
	char	*oldpwd;
	char	*newpwd;

	if (dirpwd[1] && dirpwd[2])
		return (cd_return_error());
	oldpwd = get_current_pwd();
	if (!oldpwd)
		return (2);
	err = move_to_correct_dir(envps, dirpwd);
	if (err == -1)
	{
		free(oldpwd);
		return (err);
	}
	newpwd = get_current_pwd();
	if (!newpwd)
	{
		free(oldpwd);
		return (2);
	}
	err = find_node_envp(envps, "PWD", newpwd);
	if (!err)
		err = find_node_envp(envps, "OLDPWD", oldpwd);
	return (err);
}
