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
    	input = readline("minishell$ ");
    	if (!input)
    		break ;
    	if (!*input)
    	{
    		free(input);
    		continue ;
    	}
    	else
    		add_history(input);
		execute_input(input, envp_list);
	}
	envp_free(&envp_list);
	return (0);
}
