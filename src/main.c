#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_token	*head;
	t_tree	*tree;
	t_check	flags;
	t_envp	*envp_list;

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
		char *tokens = ft_strjoin("/", input);
		t_tokens_type	signal[] = {CMD, EOFILE};
		char **pointer_token;

		//Create ENVP
		// TODO: Move envp_list out of the loop.
		// It's here to test free
		envp_list = create_envp_table(envp);

		pointer_token = (char **)ft_calloc(2, sizeof(char *));
		pointer_token[0] = tokens;
		pointer_token[1] = NULL;

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
		//ft_printf("You entered: %s\n", input);
		//tree_print(tree, 1);

		//Rebuilt ENVP function
		execution(tree, envp_list);

		envp_free(&envp_list);
		free(tokens);
		tree_free(tree);
		token_no_content_free(head);
		free(input);
	}
	return (0);
}
