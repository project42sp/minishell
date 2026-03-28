#include "../includes/minishell.h"

int	main(void)
{
	char *input;
	t_token	*head;
	t_tree	*tree;
	t_check	flags;

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
		head = token_create(tokens, signal);
		if (!head)
		{
			ft_printf("Failed to create token list\n");
			free(input);
			return (1);
		}
		tree = tree_create(head, &flags);
		ft_printf("You entered: %s\n", input);
		tree_print(tree, 0);
		tree_free(tree);
		token_list_free(head);
		free(input);
	}
	return (0);
}