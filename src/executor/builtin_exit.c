/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:53:11 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 18:06:47 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_envp *envp, t_tree *tree, char **cmd)
{
	int	err;
	int	argc;

	if (!*cmd)
		return (1);
	argc = 0;
	while (cmd[argc])
		argc++;
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	err = 0;
	if (cmd[1])
		err = ft_atoi(cmd[1]);
	envp_free(&envp);
	tree_free(&tree);
	ft_printf("exit\n");
	exit(err);
}
