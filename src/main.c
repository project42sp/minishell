/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 02:34:01 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 03:57:54 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_input(char *input, t_envp *envp_list)
{
	t_tree	*tree;
	int		status_error;

	tree = parser(input);
	if (!tree)
	{
		free(input);
		return (2);
	}
	expand_tree_args(tree, envp_list);
	status_error = execution(tree, envp_list);
	tree_free(&tree);
	free(input);
	return (status_error);
}

static int	minishell(t_envp *envp)
{
	char	*input;
	int		err;

	err = 0;
	while (1)
	{
		setup_signals();
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		else
			add_history(input);
		err = execute_input(input, envp);
		update_exit_status(envp, err);
	}
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_list;
	int		err;

	if (argc > 1)
		return (1);
	(void)*argv;
	envp_list = create_envp_table(envp);
	if (!envp_list)
	{
		perror("Error");
		return (1);
	}
	create_last_envp_node("?=0", envp_list);
	err = minishell(envp_list);
	envp_free(&envp_list);
	return (err);
}
