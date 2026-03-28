#include "../includes/minishell.h"

t_tree	*tree_pipe_create(t_token *token)
{
	t_tree	*pipe_node;
	t_tree	*right_leaf;
	t_tree	*left_leaf;

	if (!token)
		return (NULL);
	if (token->next && (token->next->signal == INPUT
      || token->next->signal == HEREDOC))
	{
		left_leaf = tree_redir_infile(token);
		token = token->next->next->next;
	}
	else
	{
		left_leaf = tree_node_create(NULL, token, NULL);
		token = token->next;
	}
	if (token->next && (token->next->signal == OUTPUT 
      || token->next->signal == APPEND))
		right_leaf = tree_redir_outfile(token->next);
	else
		right_leaf = tree_pipe_create(token->next);
	pipe_node = tree_node_create(left_leaf, token, right_leaf);
	return pipe_node;
}

t_tree	*tree_redir_infile(t_token *token)
{
	t_tree	*redir_node;
	t_tree	*leaf_node;
	t_tree	*right_node;

	if (!token)
		return (NULL);
	if (token->signal == INPUT || token->signal == HEREDOC)
	{
		leaf_node = tree_node_create(NULL, token->next, NULL);
		right_node = tree_node_create(NULL, token->next->next, NULL);
	}
	else if (token->next->signal == INPUT
			|| token->next->signal == HEREDOC)
	{
		leaf_node = tree_node_create(NULL, token->next->next, NULL);
		right_node = tree_node_create(NULL, token, NULL);
		token = token->next;
	}
	redir_node = tree_node_create(leaf_node, token, right_node);
	return (redir_node);
}

t_tree	*tree_redir_outfile(t_token *token)
{
	t_tree	*redir_node;
	t_tree	*leaf_node;
	t_tree	*right_node;

	if (!token)
		return (NULL);
	if (token->next->signal == APPEND || token->next->signal == OUTPUT)
	{
		leaf_node = tree_node_create(NULL, token, NULL);
		right_node = tree_node_create(NULL, token->next->next, NULL);
	}
	redir_node = tree_node_create(leaf_node, token, right_node);
	return (redir_node);
}
