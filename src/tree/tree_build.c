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

static t_token	*tree_redir_helper(t_token **token,
						t_tree **cmd_node, t_tree **file_node)
{
	t_token	*token_redir;
	char	**argv;

	token_redir = NULL;
	while (*token && (*token)->signal <= HEREDOC)
	{
		if ((*token)->signal == CMD)
		{
			argv = collect_args(token);
			if (!argv)
				return (NULL);
			*cmd_node = create_cmd_node(argv);
		}
		else if ((*token)->signal == FILE_PATH)
			*file_node = tree_node_create(NULL, token, NULL);
		else if ((*token)->signal >= INPUT && (*token)->signal <= HEREDOC)
		{
			token_redir = *token;
			*token = get_next_token(*token);
		}
		else
			break ;
	}
	return (token_redir);
}

static t_tree	*tree_redir(t_token **token)
{
	t_tree	*redir_node;
	t_tree	*file_node;
	t_tree	*cmd_node;
	t_token	*token_redir;
	char	**empty_argv;

	if (!*token)
		return (NULL);
	cmd_node = NULL;
	file_node = NULL;
	empty_argv = NULL;
	token_redir = tree_redir_helper(token, &cmd_node, &file_node);
	if (!cmd_node)
	{
		empty_argv = ft_calloc(1, sizeof(char *));
		cmd_node = create_cmd_node(empty_argv);
	}
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
