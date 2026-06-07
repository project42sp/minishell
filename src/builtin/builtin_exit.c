/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:53:11 by buehara           #+#    #+#             */
/*   Updated: 2026/06/05 04:02:01 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	error_message_exit(char *cmd)
{
	int	err;

	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	err = 2;
	return (err);
}

static int	parse_exit_args(char **cmd)
{
	int	argc;
	int	err;

	argc = 0;
	while (cmd[argc])
		argc++;
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	err = 0;
	if (argc == 2)
	{
		if (is_numeric(cmd[1]))
			err = ft_atoi(cmd[1]) & 255;
		else
			err = error_message_exit(cmd[1]);
	}
	return (err);
}

int	ft_exit(t_envp *envp, t_tree *tree, char **cmd)
{
	int	err;

	if (!cmd || !*cmd)
		return (1);
	err = parse_exit_args(cmd);
	if (err == -1)
		return (1);
	envp_free(&envp);
	tree_free(&tree);
	ft_printf("exit\n");
	exit(err);
}
