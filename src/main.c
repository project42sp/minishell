#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_token	*head;
	t_tree	*tree;
	t_check	flags;
	t_envp	*envp_list;
	int		fd[2];

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
		char **tokens = ft_split(input, ' ');
		size_t size = 0;
		while (tokens[size] != NULL) size++;
		char *cmd = tokens[size - 1];
		//tokens[size - 1] = ft_strjoin("/", cmd);
		free(cmd);
		t_tokens_type	signal[] = {INPUT, FILE_PATH, CMD, EOFILE};

		char **token_1 = (char **)ft_calloc(2, sizeof(char *));
		char **token_2 = (char **)ft_calloc(2, sizeof(char *));
		char **token_3 = (char **)ft_calloc(2, sizeof(char *));

		token_1[0] = tokens[0];
		token_1[1] = NULL;
		token_2[0] = tokens[1];
		token_2[1] = NULL;
		token_3[0] = tokens[2];
		token_3[1] = NULL;

		char ***pointer_token;
		pointer_token = (char ***)ft_calloc(4, sizeof(char **));
		pointer_token[0] = token_1;
		pointer_token[1] = token_2;
		pointer_token[2] = token_3;
		pointer_token[3] = NULL;

		flags.word = 1;
		flags.input = 1;
		flags.output = 0;
		flags.pipe = 0;
		flags.logical = 0;

		head = token_create(pointer_token, signal);
		if (!head)
		{
			ft_printf("Failed to create token list\n");
			free(input);
			return (1);
		}

		tree = tree_create(head, &flags);
		tree_print(tree, 0);
		tree_print_extense(tree);
		//ft_printf("You entered: %s\n", input);
		//tree_print(tree, 1);

		//Create ENVP
		// TODO: Move envp_list out of the loop.
		// It's here to test free
		envp_list = create_envp_table(envp);

		//Rebuilt ENVP function
		execution(tree, envp_list, fd);

		envp_free(&envp_list);
		tree_free(tree);
		token_no_content_free(head);
		free(input);
	}
	return (0);
}
