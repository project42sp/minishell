#include "../includes/minishell.h"

int	main(void)
{
	char *input;
	t_token	*head;
	t_tree	*tree;
	t_check	flags;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		// Adiciona ao histórico se a entrada não for vazia
		//add_history(input);
		// Hardcode - Lexer vai substituir isso depois
		t_tokens_type	signal[] = {CMD, FILE_PATH, INPUT, OUTPUT, APPEND, HEREDOC, PIPE, AND, OR, EOFILE};
		char			*tokens[] = {input, NULL};
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
		debug_lexer(head);
		ft_printf("flags: word=%d input=%d output=%d pipe=%d logical=%d\n",
		flags.word, flags.input, flags.output, flags.pipe, flags.logical);
		tree = tree_create(head, &flags);
		ft_printf("You entered: %s\n", input);
		//tree_print(tree, 1);
		free(tokens);
		free(pointer_token);
		tree_free(tree);
		token_no_content_free(head);
		free(input);
	}
	return (0);
}
