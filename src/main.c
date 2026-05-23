#include "../includes/minishell.h"

static int	execute_input(char *input, t_envp *envp_list)
{
	t_tree	*tree;
	int		status_error;

	tree = parser(input);
	if (!tree)
	{
		perror("Error");
		free(input);
		return (1);
	}
	status_error = execution(tree, envp_list);
	tree_free(&tree);
	free(input);
	return (status_error);
}

static int	minishell(t_envp *envp)
{
	char	*input;
	int		err;

	setup_signals();
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
		else
		{
			add_history(input);
		}
		err = execute_input(input, envp);
	}
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_list;
	int		err;

	if(argc > 1)
		return (1);
	(void)*argv;
	envp_list = create_envp_table(envp);
	if (!envp_list)
	{
		perror("Error");
		return (1);
	}
	err = minishell(envp_list);
	envp_free(&envp_list);
	return (err);
}
