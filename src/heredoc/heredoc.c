#include "../../includes/minishell.h"

char	*heredoc(t_envp_path *envp, char *eof)
{
	char	*input;
	char	*file;
	//Create temp file and update it's content with readline return
	// until its eof.

	(void)envp;
	file = NULL;
	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(eof) + 1))
		{
			free(input);
			break ;
		}
	}
	return (file);
}


int	find_heredoc(t_tree *tree, t_envp_path *envp)
{
	char	*file;
	int		err;

	err = 0;
	if (!tree)
		return (err);
	if (tree->signal == HEREDOC)
	{
		file = heredoc(envp, tree->node);
		free(tree->node);
		tree->node = file;
	}
	if (!file)
		err = 1;
	err = find_heredoc(tree->left, envp);
	if (!err)
		err = find_heredoc(tree->right, envp);
	return (err);
}
