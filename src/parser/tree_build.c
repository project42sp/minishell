#include "../../includes/minishell.h"

static t_tree	*tree_node_create(t_tree *left, t_token **token, t_tree *right)
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

static int	find_signal(t_token **token, int signal)
{
	t_token *temp;
	int		index;

	temp = *token;
	index = 0;
	while(temp->next != NULL || temp->signal != signal)
	{
		index++;
		temp = temp->next;
	}
	return (index);
}

static int	token_counter(t_token **token)
{
	t_token	*temp;
	int		len;

	temp = *token;
	len = 0;
	while (temp->next != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

t_tree	*tree_wrapper(t_tree *left, t_token **tk, t_tree *right, t_tree *old)
{
	t_tree	*node;

	if (!*tk || !old)
		return (NULL);
	node = tree_node_create(left, tk, right);
	if (!node)
	{
		tree_free(&old);
	}
	return (node);
}

static t_tree	*tree_redir_helper(t_token **token)
{
	t_token	*token_redir;
	t_tree	*cmd;
	t_tree	*file;
	t_tree	*redir;

	if (token_counter(token) != 3 || find_signal(token, PIPE) != 4)
		return (NULL);
	token_redir = NULL;
	cmd = NULL;
	file = NULL;
	redir = NULL;
	while (*token && (*token)->signal <= HEREDOC)
	{
		if ((*token)->signal == CMD)
		{
			cmd = tree_wrapper(NULL, token, NULL, file);
			if (!cmd)
				return (NULL);
		}
		else if ((*token)->signal == FILE_PATH)
		{
			file = tree_wrapper(NULL, token, NULL, cmd);
			if (!file)
				return (NULL);
		}
		else if ((*token)->signal >= INPUT && (*token)->signal <= HEREDOC)
		{
			token_redir = *token;
			*token = get_next_token(*token);
		}
	}
	redir = tree_node_create(file, &token_redir, cmd);
	if (!redir)
	{
		tree_free(&file);
		tree_free(&cmd);
		return (NULL);
	}
	return (redir);
}

static t_tree	*tree_redir(t_token **token)
{
	t_tree	*redir_node;
	t_tree	*left;
	t_tree	*right;
	t_token	*token_redir;

	if (!*token)
		return (NULL);
	right = NULL;
	left = NULL;
	token_redir = NULL;
//	if (!(*token)->next || (*token)->next->signal > HEREDOC)
//	{
//		right = tree_node_create(NULL, token, NULL);
//		if (!right)
//			return (NULL);
//		return (right);
//	}
	//token_redir = tree_redir_helper(token);
//	redir_node = tree_redir(&(*token)->next);
//	if (!redir_node)
//		return (right);
//	redir_node = tree_node_create(left, &token_redir, right);
//	if (!redir_node)
//		return (NULL);
//	return (redir_node);
	if ((*token)->signal == CMD)
	{
		right = tree_node_create(NULL, token, NULL);
	}

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
	if (token_counter(token) == 3)
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
