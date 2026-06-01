/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 10:21:44 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 10:21:46 by buehara          ###   ########.fr       */
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
	cmd = (char **)tree->node;
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		err = ft_env(envps->envp);
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
		err = ft_echo(envps->envp, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		err = ft_pwd();
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		err = ft_cd(envps, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		err = ft_unset(&envps->envp_og, cmd);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		err = ft_export(&envps->envp_og, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		err = ft_exit(envps, cmd);
	return (err);
}
