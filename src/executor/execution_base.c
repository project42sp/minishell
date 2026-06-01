/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:21:33 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 18:27:00 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_free(t_envp_path *envps)
{
	if (!envps)
		return ;
	if (envps->envp_og)
		envp_free(&envps->envp_og);
	if (envps->root)
		tree_free(&envps->root);
	if (envps)
		envp_path_free(&envps);
}

static int	child_process(t_tree *tree, t_envp_path *envps)
{
	char	*full_path;
	char	**node;

	node = (char **)tree->node;
	if (!node || !node[0])
	{
		child_free(envps);
		exit(0);
	}
	full_path = find_path(envps->path, node);
	if (!full_path)
	{
		child_free(envps);
		perror("Error");
		exit(2);
	}
	execve(full_path, node, envps->envp);
	free(full_path);
	child_free(envps);
	perror("Error");
	exit(127);
}

int	redir_control(t_tree **tree, t_fd *fd)
{
	if (redirect(tree, fd))
	{
		if (fd)
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
		return (1);
	}
	if (fd)
	{
		ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
	}
	return (0);
}

int	base_exec(t_envp_path *envps, t_tree *tree, t_fd *fd)
{
	int		err;

	err = 0;
	envps->pid->pid[envps->pid->index] = fork();
	if (envps->pid->pid[envps->pid->index] == 0)
	{
		set_signals_default();
		signal(SIGPIPE, SIG_DFL);
		if (redir_control(&tree, fd) != 0)
		{
			child_free(envps);
			exit(1);
		}
		envps->root = tree;
		if (!tree->node || !((char **)tree->node)[0])
		{
			child_free(envps);
			exit(0);
		}
		err = check_builtin(envps, tree);
		if (err != -1)
		{
			child_free(envps);
			exit(2);
		}
		err = child_process(tree, envps);
		child_free(envps);
	}
	if (fd)
		ft_close(fd->fd[1], fd->oldfd, -1, -1);
	envps->pid->index++;
	return (err);
}

int	execution(t_tree *tree, t_envp *envp_table)
{
	t_envp_path	*envp_struct;
	int			status_code;

	if (!tree || !envp_table)
		return (1);
	signal(SIGPIPE, SIG_IGN);
	status_code = 0;
	envp_struct = create_envp_struct(tree, envp_table);
	if (!envp_struct)
	{
		perror("Malloc");
		return (1);
	}
	if (has_invalid_source(tree))
	{
		envp_path_free(&envp_struct);
		return (2);
	}
	ignore_signals();
	if (tree->signal != CMD)
		status_code = pipe_exec(envp_struct, tree, -1);
	else
	{
		status_code = check_builtin(envp_struct, tree);
		if (status_code == -1)
			status_code = base_exec(envp_struct, tree, NULL);
	}
	status_code = ft_wait(envp_struct->pid, status_code);
	setup_signals();
	envp_path_free(&envp_struct);
	return (status_code);
}
