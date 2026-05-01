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

static t_token	*tree_redir_helper(t_token **token,
						t_tree **cmd_node, t_tree **file_node)
{
	t_token	*token_redir;
	t_tree	*last_cmd;
	t_tree	*new_cmd;

	token_redir = NULL;
	last_cmd = NULL;
	while (*token && (*token)->signal <= HEREDOC)
	{
		if ((*token)->signal == CMD)
		{
			new_cmd = tree_node_create(NULL, token, NULL);
			if (!*cmd_node)
			{
				*cmd_node = new_cmd;
				last_cmd = new_cmd;
			}
			else
			{
				last_cmd->right = new_cmd;
				last_cmd = new_cmd;
			}
		}
		else if ((*token)->signal == FILE_PATH)
			*file_node = tree_node_create(NULL, token, NULL);
		else if ((*token)->signal >= INPUT && (*token)->signal <= HEREDOC)
		{
			token_redir = *token;
			*token = get_next_token(*token);
		}
	}
	return (token_redir);
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
	token_redir = NULL;
	if (!(*token)->next || (*token)->next->signal > HEREDOC)
	{
		cmd_node = tree_node_create(NULL, token, NULL);
		return (cmd_node);
	}
	token_redir = tree_redir_helper(token, &cmd_node, &file_node);
	if (!token_redir)
		return (cmd_node);
	redir_node = tree_node_create(file_node, &token_redir, cmd_node);
	return (redir_node);
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
