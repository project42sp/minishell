/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:53:11 by buehara           #+#    #+#             */
/*   Updated: 2026/05/31 20:53:13 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_envp *envp, t_tree *tree, char **cmd)
{
	int	err;

	err = 0;
	if (!*cmd)
		return (1);
	if (cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (cmd[1])
		err = ft_atoi(cmd[1]);
	envp_free(&envp);
	tree_free(&tree);
	ft_printf("exit\n");
	exit(err);
}
