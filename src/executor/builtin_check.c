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

int	check_builtin(t_envp *envp, t_tree *tree)
{
	char	**cmd;

	if (!tree || !tree->node)
		return (-1);
	cmd = ((char **)tree->node);
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(envp));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(envp, cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(envp, cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(&envp, cmd));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(&envp, cmd));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(envp, tree, cmd));
	else
		if (has_invalid_source(tree))
			return (1);
	return (-1);
}
