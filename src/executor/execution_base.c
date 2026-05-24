/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:21:33 by buehara           #+#    #+#             */
/*   Updated: 2026/05/16 21:21:38 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_free(t_envp_path *envps)
{
	envp_free(&envps->envp_og);
	tree_free(&envps->root);
	envp_path_free(&envps);
}

static int	child_process(t_tree *tree, t_envp_path *envps)
{
	char	*full_path;
	char	**node;

	node = (char **)tree->node;
	full_path = find_path(envps->path, node);
	if (!full_path)
	{
		child_free(envps);
		perror("Error");
		exit(2);
	}
	execve(full_path, node, envps->envp);
	free(full_path);
	perror("Error");
	exit(127);
}

int	redir_control(t_tree **tree, t_fd *fd)
{
	if (redirect(tree, fd))
	{
		tree_free(tree);
		if (fd)
		{
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
			free(fd);
		}
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
		signal(SIGPIPE, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (redir_control(&tree, fd) != 0)
			exit(1);
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
	if (tree->signal != CMD)
		status_code = pipe_exec(envp_struct, tree, -1);
	else
	{
		status_code = check_builtin(envp_struct, tree);
		if (status_code == -1)
			status_code = base_exec(envp_struct, tree, NULL);
	}
	status_code = ft_wait(envp_struct->pid, status_code);
	envp_path_free(&envp_struct);
	return (status_code);
}
