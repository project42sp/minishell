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
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		err = ft_env(envps->envp);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		err = ft_echo(envps->envp, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		err = ft_pwd();
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		err = ft_cd(envps, cmd);
	return (err);
}
