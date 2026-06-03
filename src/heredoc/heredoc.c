#include "../../includes/minishell.h"

char	*heredoc(t_envp *envp, char *eof)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(eof) + 1))
		{
			free(input);
			break ;
		}
	}
}

int	find_heredoc(t_tree *tree, t_envp *envp)
{
	char	*eof;
	char	*file;

	if (tree->signal == HEREDOC)
	{
		file = heredoc(envp, tree->node);
		free(tree->node);
		tree->node = file;
	}
	find_heredoc(tree->left, envp);
	find_heredoc(tree->right, envp);
}
