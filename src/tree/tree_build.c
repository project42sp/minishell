/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:23:51 by buehara           #+#    #+#             */
/*   Updated: 2026/06/05 05:41:38 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*tree_node_create(t_tree *left, t_token **token, t_tree *right)
{
	t_tree	*tree;

	if (!*token)
		return (NULL);
	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->left = left;
	tree->signal = (*token)->signal;
	tree->node = (*token)->token;
	(*token)->token = NULL;
	tree->right = right;
	*token = (*token)->next;
	return (tree);
}

t_tree	*tree_redir_helper(t_token **token, t_tree *cmd_node)
{
//	t_tree	*file_node;

	if (!*token || (*token)->signal > HEREDOC)
		return (cmd_node);
	if ((*token)->signal == CMD)
		return (handle_cmd_token(token, cmd_node));
	if ((*token)->signal == FILE_PATH)
	{
	//	file_node = tree_node_create(NULL, token, NULL);
		return (tree_redir_helper(token, cmd_node));
	}
	return (handle_redir_token(token, cmd_node));
}

static t_tree	*tree_redir(t_token **token)
{
	t_tree	*cmd_node;
	char	**empty_argv;

	if (!*token)
		return (NULL);
	empty_argv = ft_calloc(1, sizeof(char *));
	if (!empty_argv)
		return (NULL);
	cmd_node = create_cmd_node(empty_argv);
	if (!cmd_node)
	{
		free(empty_argv);
		return (NULL);
	}
	return (tree_redir_helper(token, cmd_node));
}

static t_tree	*tree_pipe_create(t_token **token)
{
	t_tree	*pipe_node;
	t_tree	*right_node;
	t_tree	*left_node;
	t_token	*pipe_token;

	if (!*token)
		return (NULL);
	right_node = NULL;
	left_node = NULL;
	left_node = tree_redir(token);
	if (!*token || (*token)->signal != PIPE)
		return (left_node);
	pipe_token = *token;
	*token = (*token)->next;
	right_node = tree_pipe_create(token);
	pipe_node = tree_node_create(left_node, &pipe_token, right_node);
	return (pipe_node);
}

t_tree	*tree_create(t_token *token, t_check *flags)
{
	t_tree	*tree;

	if (!token || !flags)
		return (NULL);
	tree = NULL;
	if (flags->pipe)
		tree = tree_pipe_create(&token);
	else if (flags->input || flags->output || flags->word)
		tree = tree_redir(&token);
	return (tree);
}
