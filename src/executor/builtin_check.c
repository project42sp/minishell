/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 10:21:44 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 16:39:12 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_builtin(t_envp_path *envps, t_tree *tree)
{
	char	**cmd;
	int		err;

	if (!tree || !tree->node)
		return (2);
	err = -1;
	cmd = ((char **)tree->node);
	if (!cmd)
		return (err);
	if (ft_strcmp(cmd[0], "env") == 0)
		err = ft_env(envps->envp);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		err = ft_echo(envps->envp, cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		err = ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		err = ft_cd(envps, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		err = ft_unset(&envps->envp_og, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		err = ft_export(&envps->envp_og, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		err = ft_exit(envps, cmd);
	return (err);
}
