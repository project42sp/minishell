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

void	child_free(t_tree *tree, t_envp_path *envps, t_fd *fd, t_pid *pid)
{
	if (fd)
	{
		ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
		free(fd);
	}
	free(pid->pid);
	free(pid);
	envp_free(&envps->envp_og);
	envp_path_free(&envps);
	tree_free(&tree);
}

static int	child_process(t_tree *tree, t_envp_path *envps, t_fd *fd, t_pid *pid)
{
	char	*full_path;
	char	**node;

	node = (char **)tree->node;
	full_path = find_path(envps->path, node);
	if (!full_path)
	{
		child_free(tree, envps, fd, pid);
		perror("Error path");
		exit(2);
	}
	execve(full_path, node, envps->envp);
	free(full_path);
	child_free(tree, envps, fd, pid);
	perror("Error exec");
	exit(127);
}

int	base_exec(t_envp_path *envps, t_tree *tree, t_fd *fd, t_pid *pid)
{
	int		err;

	//if (builtin)
		//Run builtin
		// Return status code
	err = 0;
	pid->pid[pid->index] = fork();
	if (pid->pid[pid->index] == 0)
	{
		signal(SIGPIPE, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (redirect(&tree, fd))
			exit(1);
		if (fd)
			ft_close(fd->fd[0], fd->fd[1], fd->oldfd, -1);
		err = child_process(tree, envps, fd, pid);
	}
	if (fd)
		ft_close(fd->fd[1], fd->oldfd, -1, -1);
	pid->index++;
	tree_free(&tree);
	return (err);
}

t_pid	*pid_create_free(t_tree *tree, t_envp_path *envp)
{
	t_pid	*pid;

	if (!tree || !envp)
		return (NULL);
	pid = create_pid(tree);
	if (!pid)
	{
		tree_free(&tree);
		envp_path_free(&envp);
		return (NULL);
	}
	return (pid);
}

void	pid_free(t_pid **pid)
{
	if (!*pid)
		return ;
	if ((*pid)->pid)
		free((*pid)->pid);
	free(*pid);
	*pid = NULL;
}

int	execution(t_tree *tree, t_envp *envp_table)
{
	t_envp_path	*envp_struct;
	t_pid		*pid;
	int			status_code;

	if (!tree || !envp_table)
		return (1);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	status_code = 0;
	envp_struct = create_envp_struct(envp_table);
	if (!envp_struct)
	{
		perror("Malloc");
		return (1);
	}
	pid = pid_create_free(tree, envp_struct);
	if (!pid)
		return (1);
	if (tree->signal != CMD)
		status_code = pipe_exec(envp_struct, tree, -1, pid);
	else
		status_code = base_exec(envp_struct, tree, NULL, pid);
	status_code = ft_wait(pid);
	pid_free(&pid);
	envp_path_free(&envp_struct);
	return (status_code);
}
