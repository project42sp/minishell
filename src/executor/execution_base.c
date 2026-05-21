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

static int	child_process(t_tree *tree, t_envp_path *envps, t_fd *fd)
{
	char	*full_path;
	char	**node;

	node = (char **)tree->node;
	full_path = find_path(envps->path, node);
	if (!full_path)
	{
		if (fd)
		{
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
			free(fd);
		}
		envp_path_free(&envps);
		tree_free(&tree);
		perror("Error");
		exit(2);
	}
	execve(full_path, node, envps->envp);
	if (fd)
		free(fd);
	free(full_path);
	envp_path_free(&envps);
	tree_free(&tree);
	perror("Error");
	exit(127);
}

int	base_exec(t_envp_path *envps, t_tree *tree, t_fd *fd)
{
	int		err;
	pid_t	pid;

	//if (builtin)
		//Run builtin
		// Return status code
	err = 0;
	pid = fork();
	if (pid == 0)
	{
		if (redirect(&tree, fd))
			exit(1);
		if (fd)
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
		err = child_process(tree, envps, fd);
	}
	if (fd)
		ft_close(fd->fd[1], fd->oldfd, -1, -1);
	tree_free(&tree);
	return (err);
}

int	execution(t_tree *tree, t_envp *envp_table)
{
	t_envp_path	*envp_struct;
	int			status_code;

	if (!tree || !envp_table)
		return (1);
	status_code = 0;
	envp_struct = create_envp_struct(envp_table);
	if (!envp_struct)
	{
		perror("Malloc");
		return (1);
	}
	if (tree->signal != CMD)
		status_code = pipe_exec(envp_struct, tree, -1);
	else
		status_code = base_exec(envp_struct, tree, NULL);
	status_code = ft_wait();
	split_free(envp_struct->envp);
	split_free(envp_struct->path);
	free(envp_struct);
	return (status_code);
}
