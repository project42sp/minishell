#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "token.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef struct s_tree
{
	int				signal;
	void			*node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//t_tree	*tree_node_create(t_tree *left, void *token, t_tree *right);
void	tree_print(t_tree *tree, int level);
t_tree	*tree_create(t_token *list, t_check *flags);
t_token	*token_create(char **tokens, t_tokens_type *signal);

void	tree_print_extense(t_tree *tree); 

// Free functions
void	token_list_free(t_token *head);
void	tree_free(t_tree *tree);

#endif