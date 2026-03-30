#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_token	*head;
	t_tree	*tree;
	t_check	flags;

	if(argc > 1)
		return (1);
	(void)*argv;
	while(1)
	{
		input = readline("minishell$ ");
		// ctrk + D para sair do shell
		if (!input)
			break;
		if (!*input)
		{
			free(input);
			continue ;
		}
		//add_history(input);

		// Hardcode - Lexer vai substituir isso depois
<<<<<<< HEAD
		t_tokens_type	signal[] = {CMD, FILE_PATH, INPUT, OUTPUT, APPEND, HEREDOC, PIPE, AND, OR, EOFILE};

		char *tokens = ft_strdup(input);
		char **pointer_token;

		pointer_token = (char **)ft_calloc(2, sizeof(char *));
		pointer_token[0] = tokens;
		pointer_token[1] = NULL;
=======
		t_tokens_type	signal[] = {CMD, EOFILE};
		char			*tokens[] = {input, NULL};
>>>>>>> aaa6f6c (chore: add executor tests)
		flags.word = 1;
		flags.input = 0;
		flags.output = 0;
		flags.pipe = 0;
		flags.logical = 0;
		head = token_create(&pointer_token, signal);
		if (!head)
		{
			ft_printf("Failed to create token list\n");
			free(input);
			return (1);
		}
		tree = tree_create(head, &flags);
		ft_printf("You entered: %s\n", input);
<<<<<<< HEAD
		//tree_print(tree, 1);
		free(tokens);
		free(pointer_token);
=======

		execution(tree, envp);
	//	tree_print(tree, 0);
>>>>>>> aaa6f6c (chore: add executor tests)
		tree_free(tree);
		token_no_content_free(head);
		free(input);
	}
	return (0);
}
