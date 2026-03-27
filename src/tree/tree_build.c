# include "../includes/minishell.h"

static t_token	*get_next_token(t_token *token)
{
	if (!token)
		return NULL;
	if (token->next != NULL)
		//free
		return token->next;
	return token;
}

static t_tree *tree_node_create(t_tree *left, t_token **token, t_tree *right)
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
	tree->right = right;
	*token = (*token)->next;
	return (tree);
}

static t_tree	*tree_redir(t_token **token)
{
	t_tree	*redir_node;
	t_tree	*file_node;
	t_tree	*cmd_node;
	t_token	*token_redir;

	if (!*token)
		return (NULL);
	cmd_node = NULL;
	file_node = NULL;
	if (!(*token)->next || (*token)->next->signal > HEREDOC)
	{
		cmd_node = tree_node_create(NULL, token, NULL);
		return (cmd_node);
	}
	while (*token && (*token)->signal <= HEREDOC)
	{
		if ((*token)->signal == CMD)
			cmd_node = tree_node_create(NULL, token, NULL);
		else if ((*token)->signal == FILE_PATH)
			file_node = tree_node_create(NULL, token, NULL);
		else if ((*token)->signal >= INPUT && (*token)->signal <= HEREDOC)
		{
			token_redir = *token;
			*token = get_next_token(*token);
		}
	}
	redir_node = tree_node_create(file_node, &token_redir, cmd_node);
	return (redir_node);
}

static t_tree	*tree_pipe_create(t_token **token)
{
	t_tree	*pipe_node;
	t_tree	*right_node;
	t_tree	*left_node;

	if (!*token)
		return (NULL);
	right_node = NULL;
	left_node = NULL;
	if (*token)
		left_node = tree_redir(token);
	if (*token && (*token)->signal == PIPE)
		right_node = tree_pipe_create(&(*token)->next);
	else
		return (left_node);
	pipe_node = tree_node_create(left_node, token, right_node);
	return pipe_node;
}

t_tree	*tree_create(t_token *token, t_check *flags)
{
	t_tree	*tree;

	if (!token || !flags)
		return (NULL);
	// Precedense of logical operators over pipe operator.
	// Will need to add an if and change the pipe's if to else if
	tree = NULL;
	if (flags->pipe)
		tree = tree_pipe_create(&token);
	else if (flags->input || flags->output)
		tree = tree_redir(&token);
	else if (flags->word)
		tree = tree_node_create(NULL, &token, NULL);
	return tree;
}