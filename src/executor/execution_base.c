/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:21:33 by buehara           #+#    #+#             */
/*   Updated: 2026/06/05 04:30:59 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	child_err(t_envp_path *envps, int flag)
{
	child_free(envps);
	if (flag)
		perror("Error");
	exit(2);
}

static int	child_process(t_tree *tree, t_envp_path *envps)
{
	char	*full_path;
	char	**node;
	int		err;

	err = 0;
	node = (char **)tree->node;
	err = check_builtin_child(envps, envps->envp_og, tree);
	if (err != -1)
		child_err(envps, 0);
	full_path = find_path(envps->path, node);
	if (!full_path)
		child_err(envps, 1);
	signal(SIGPIPE, SIG_DFL);
	execve(full_path, node, envps->envp);
	free(full_path);
	child_free(envps);
	perror("Error");
	exit(127);
}

int	base_exec(t_envp_path *envps, t_tree *tree, t_fd *fd)
{
	int		err;

	err = 0;
	signal(SIGPIPE, SIG_IGN);
	envps->pid->pid[envps->pid->index] = fork();
	if (envps->pid->pid[envps->pid->index] == 0)
	{
		set_signals_default();
		if (redir_control(&tree, fd) != 0)
		{
			child_free(envps);
			exit(1);
		}
		if (!tree || !tree->node || !((char **)tree->node)[0])
		{
			child_free(envps);
			exit(0);
		}
		err = child_process(tree, envps);
		child_free(envps);
	}
	if (fd)
		ft_close(fd->fd[1], fd->oldfd, -1, -1);
	envps->pid->index++;
	return (err);
}

int	call_commands(t_envp_path *envp_struct, t_tree *tree)
{
	int	status_code;

	status_code = 0;
	ignore_signals();
	envp_struct->root = tree;
	if (tree->signal != CMD)
		status_code = pipe_exec(envp_struct, tree, -1);
	else
		status_code = base_exec(envp_struct, tree, NULL);
	status_code = ft_wait(envp_struct->pid, status_code);
	setup_signals();
	return (status_code);
}

int	execution(t_tree *tree, t_envp *envp_table)
{
	t_envp_path	*envp_struct;
	int			status_code;
	char		**cmd;

	if (!tree || !envp_table)
		return (1);
	if (tree->signal == CMD && tree->node)
	{
		cmd = (char **)tree->node;
		if (cmd && cmd[0] && ft_strcmp(cmd[0], "exit") == 0)
		{
			status_code = ft_exit(envp_table, tree, cmd);
			return (status_code);
		}
	}
	status_code = find_heredoc(tree, 0, envp_table);
	status_code = check_builtin(envp_table, tree);
	if (status_code != -1)
		return (status_code);
	envp_struct = create_envp_struct(tree, envp_table);
	if (!envp_struct)
		return (1);
	status_code = call_commands(envp_struct, tree);
	envp_path_free(&envp_struct);
	return (status_code);
}
