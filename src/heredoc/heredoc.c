/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 03:53:53 by buehara           #+#    #+#             */
/*   Updated: 2026/06/05 05:41:46 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_warning(t_heredoc *hd, int counter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(counter, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(hd->eof, 2);
	ft_putendl_fd("')\n", 2);
	return (1);
}

static int	heredoc_write(t_heredoc *hd, char *input)
{
	char	*expanded;

	expanded = expand_argument(input, hd->envp);
	free(input);
	if (!expanded)
		return (1);
	ft_putendl_fd(expanded, hd->fd);
	free(expanded);
	return (0);
}

static int	heredoc_readline(t_heredoc *hd, int counter)
{
	char	*input;

	input = readline("> ");
	if (g_signal == SIGINT)
	{
		free(input);
		return (1);
	}
	if (!input)
		return (heredoc_warning(hd, counter));
	if (ft_strncmp(input, hd->eof, hd->size + 1) == 0)
	{
		free(input);
		return (1);
	}
	return (heredoc_write(hd, input));
}

char	**heredoc(char *eof, int index, t_envp *envp)
{
	t_heredoc	data;
	char		**file;
	int			err;
	int			counter;

	data.eof = eof;
	data.size = ft_strlen(eof);
	data.envp = envp;
	file = create_temp_file(eof, index, &data.fd);
	if (!file)
		return (NULL);
	err = 0;
	counter = 0;
	setup_signals_heredoc();
	while (err == 0)
	{
		err = heredoc_readline(&data, counter);
		counter++;
	}
	ignore_signals();
	setup_signals();
	close(data.fd);
	return (file);
}

int	find_heredoc(t_tree *tree, int index, t_envp *envp)
{
	char	**file;
	int		err;

	if (!tree)
		return (1);
	if (tree->signal != HEREDOC)
	{
		err = find_heredoc(tree->right, index + 1, envp);
		if (err)
			return (1);
		err = find_heredoc(tree->left, index + 2, envp);
		if (err)
			return (1);
	}
	else
	{
		file = heredoc(((char **)tree->left->node)[0], index, envp);
		if (!file)
			return (1);
		split_free(tree->left->node);
		tree->left->node = (void *)file;
	}
	return (0);
	}
