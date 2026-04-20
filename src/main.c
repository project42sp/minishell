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
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);

		ft_bzero(&flags, sizeof(t_check));
		tokens = lexer(input, &signals, &flags);
		if (!tokens)
		{
			ft_printf("Lexer error: invalid syntax\n");
			free(input);
			continue ;
		}
		head = token_create(tokens, signals);
		if (!head)
		{
			ft_printf("Failed to create token list\n");
			free(tokens);
			free(signals);
			free(input);
			continue ;
		}
		debug_lexer(head);
		ft_printf("flags: word=%d input=%d output=%d pipe=%d logical=%d\n",
			flags.word, flags.input, flags.output, flags.pipe, flags.logical);
		token_list_free(head);
		free(tokens);
		free(signals);
		free(input);
	}
	return (0);
}