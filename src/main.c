#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
//	t_token	*head;
	t_tree	*tree;
//	t_check	flags;
	t_envp	*envp_list;
//	t_tokens_type	*signals;
//	char ***tokens;

	if(argc > 1)
		return (1);
	(void)*argv;
	while(1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);

//		tokens = lexer(input, &signals, &flags);
//		if (!tokens)
//		{
//			ft_printf("Lexer error: invalid syntax\n");
//			free(input);
//			continue ;
//		}
//
//		head = token_create(tokens, signals);
//		if (!head)
//		{
//			ft_printf("Failed to create token list\n");
//			free(tokens);
//			free(signals);
//			free(input);
//			continue ;
//		}
//
//		tree = tree_create(head, &flags);

		tree = parser(input);
		if (!tree)
		{
			perror("Error");
			free(input);
			continue ;
		}
		envp_list = create_envp_table(envp);

		//Rebuilt ENVP function
		execution(tree, envp_list);

//		token_list_free(head);
		envp_free(&envp_list);
//		free(tokens);
//		free(signals);
//		free(input);
	}
	return (0);
}
