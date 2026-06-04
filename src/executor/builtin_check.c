/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 10:21:44 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 03:59:10 by buehara          ###   ########.fr       */
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

	if (!tree || !tree->node)
		return (2);
	cmd = ((char **)tree->node);
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(envps->envp));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(envps->envp, cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(envps, cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_unset(&envps->envp_og, cmd));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_export(&envps->envp_og, cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(envps, cmd));
	else
		if (has_invalid_source(tree))
			return (1);
	return (-1);
}
