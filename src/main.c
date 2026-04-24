#include "../includes/minishell.h"

static char	*get_input(void)
{
	char *input;

	input = readline("minishell$ ");
	if (!input)
		return (NULL);
	if (!*input)
	{
	    free(input);
    	return (NULL);
	}
	else
    	add_history(input);
	return (input);
}

static void	execute_input(char *input, t_envp *envp_list)
{
	t_tree	*tree;

	tree = parser(input);
	if (!tree)
	{
		perror("Error");
		free(input);
		return ;
	}
	execution(tree, envp_list);
	free(input);
}

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_envp	*envp_list;

	if(argc > 1)
		return (1);
	(void)*argv;
	envp_list = create_envp_table(envp);
	if (!envp_list)
	{
		perror("Error");
		return (1);
	}
	while(1)
	{
		input = get_input();
		if (!input)
			break ;
		execute_input(input, envp_list);
	}
	envp_free(&envp_list);
	return (0);
}
