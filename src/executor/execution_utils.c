/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:19:53 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 02:37:17 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd3);
	if (fd4 > -1)
		close(fd4);
}

t_fd	fd_create(int old_fd)
{
	t_fd	fd;

	fd.fd[0] = -1;
	fd.fd[1] = -1;
	fd.oldfd = old_fd;
	fd.last = 0;
	return (fd);
}

int	ft_wait(t_pid *pid, int status_code)
{
	int	status;
	int	exit_code;
	int	index;

	exit_code = 0;
	index = 0;
	status = status_code;
	while (index < pid->size)
	{
		waitpid(pid->pid[index], &status, 0);
		if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		index++;
	}
	return (exit_code);
}

int	has_invalid_source(t_tree *tree)
{
	char **cmd;

	if (!tree)
		return (0);
	if (tree->signal == CMD)
	{
		cmd = (char **)tree->node;
		if (cmd && ft_strcmp(cmd[0], ".") == 0 && !cmd[1])
		{
			ft_putstr_fd("minishell: .: filename argument required\n", 2);
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
			return (1);
		}
	}
	if (has_invalid_source(tree->left))
		return (1);
	return (has_invalid_source(tree->right));
}