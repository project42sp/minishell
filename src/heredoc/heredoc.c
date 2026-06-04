/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 03:53:53 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 03:53:54 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*create_temp_path_name(char *eof, int index)
{
	char	*name_pid;
	char	*name_index;
	char	*pid;
	char	*index_char;

	pid = ft_itoa(getpid());
	if (!pid)
		return (NULL);
	name_pid = ft_strjoin(eof, pid);
	free(pid);
	if (!name_pid)
		return (NULL);
	index_char = ft_itoa(index);
	if (!index_char)
	{
		free(name_pid);
		return (NULL);
	}
	name_index = ft_strjoin(name_pid, index_char);
	free(index_char);
	free(name_pid);
	if (!name_index)
		return (NULL);
	return (name_index);
}

char	**create_temp_file(char *eof, int index, int *fd)
{
	char	*file;
	char	*full_path;
	char	**file_node;

	file = create_temp_path_name(eof, index);
	if (!file)
		return (NULL);
	full_path = ft_strjoin("/tmp/.", file);
	free(file);
	if (!full_path)
		return (NULL);
	*fd = open(full_path, O_RDWR | O_CREAT, 0600);
	if (*fd == -1)
	{
		free(full_path);
		return (NULL);
	}
	file_node = (char **)ft_calloc(sizeof(char *), 2);
	if (!file_node)
	{
		free(full_path);
		return (NULL);
	}
	file_node[0] = full_path;
	return (file_node);
}

static int	heredoc_readline(char *eof, int size, int fd, int counter)
{
	char	*input;

	input = readline("> ");
	if (g_signal == SIGINT)
	{
		free(input);
		return (1);
	}
	if (!input)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(counter, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(eof, 2);
		ft_putendl_fd("')\n", 2);
		return (1);
	}
	if (ft_strncmp(input, eof, size + 1) == 0)
	{
		free(input);
		return (1);
	}
	// Expander function here
	ft_putendl_fd(input, fd);
	return (0);
}

char	**heredoc(char *eof, int index)
{
	char	**file;
	int		size;
	int		fd;
	int		err;
	int		counter;

	size = ft_strlen(eof);
	file = create_temp_file(eof, index, &fd);
	if (!file)
		return (NULL);
	err = 0;
	counter = 0;
	setup_signals_heredoc();
	while (err == 0)
	{
		err = heredoc_readline(eof, size, fd, counter);
		counter++;
	}
	ignore_signals();
	setup_signals();
	close(fd);
	return (file);
}

int	find_heredoc(t_tree *tree, int index)
{
	char	**file;
	int		err;

	err = 0;
	if (!tree)
		return (err);
	file = NULL;
	if (tree->signal == HEREDOC)
	{
		file = heredoc(((char **)tree->left->node)[0], index);
		split_free(tree->left->node);
		tree->left->node = (void *)file;
	}
	if (!file)
		err = 1;
	err = find_heredoc(tree->left, index + 1);
	if (!err)
		err = find_heredoc(tree->right, index + 2);
	return (err);
}
