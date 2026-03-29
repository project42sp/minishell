#include "../includes/minishell.h"

int	main(void)
{
	t_tree	*tree;
	t_tokens_type signals[] = {INPUT, FILE_PATH, CMD, PIPE, CMD, OUTPUT, FILE_PATH};
	char	*lst_tokens[] = {"<", "file", "wc", "|", "grep", ">", "outfile.txt", NULL};
	t_token	*tokens;
	t_token	*head;
	t_check	flags;

	tokens = token_create(lst_tokens, signals);
	head = tokens;

	if (!tokens)
		return (1);
	while (tokens != NULL)
	{
		ft_printf("token: %s\t\t|\tsignal: %d\n", tokens->token, tokens->signal);
		tokens = tokens->next;
	}

	flags.word = 1;
	flags.input = 1;
	flags.output = 1;
	flags.pipe = 1;
	flags.logical = 0;

	tree = tree_create(head, &flags);

	ft_printf("\nTree Built: \n");
	tree_print(tree, 0);
	ft_printf("\nToken re-built: ");
	tree_print_extense(tree);
	ft_printf("\n\n");

	t_tokens_type signals2[] = {CMD, PIPE, CMD, PIPE, CMD, PIPE, CMD};
	char	*lst_tokens2[] = {"cmd1", "|", "cmd2", "|", "cmd3", "|", "cmd4", NULL};

	tokens = token_create(lst_tokens2, signals2);
	head = tokens;

	if (!tokens)
		return (1);
	while (tokens != NULL)
	{
		ft_printf("token: %s\t\t|\tsignal: %d\n", tokens->token, tokens->signal);
		tokens = tokens->next;
	}

	flags.word = 1;
	flags.input = 0;
	flags.output = 0;
	flags.pipe = 1;
	flags.logical = 0;

	tree = tree_create(head, &flags);

	ft_printf("\nTree Built: \n");
	tree_print(tree, 0);
	ft_printf("\nToken re-built: ");
	tree_print_extense(tree);
	ft_printf("\n");

	t_tokens_type signals3[] = {CMD, PIPE, CMD, OUTPUT, FILE_PATH, PIPE, CMD, PIPE, CMD};
	char	*lst_tokens3[] = {"cmd1", "|", "cmd2", ">", "file1", "|", "cmd3", "|", "cmd4", NULL};

	tokens = token_create(lst_tokens3, signals3);
	head = tokens;

	if (!tokens)
		return (1);
	while (tokens != NULL)
	{
		ft_printf("token: %s\t\t|\tsignal: %d\n", tokens->token, tokens->signal);
		tokens = tokens->next;
	}

	flags.word = 1;
	flags.input = 0;
	flags.output = 1;
	flags.pipe = 1;
	flags.logical = 0;

	tree = tree_create(head, &flags);

	ft_printf("\nTree Built: \n");
	tree_print(tree, 0);
	ft_printf("\nToken re-built: ");
	tree_print_extense(tree);
	ft_printf("\n");
	return (0);
}
