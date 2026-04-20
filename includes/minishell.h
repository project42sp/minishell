#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "token.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_tree
{
	int				signal;
	void			*node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

//Test Functions
void	tree_print(t_tree *tree, int level);
void	tree_print_extense(t_tree *tree);

// Token Create Functions
t_tree	*tree_create(t_token *list, t_check *flags);
t_token	*token_create(char ***tokens, t_tokens_type *signal);
t_token	*get_next_token(t_token *token);

// Free functions
void	token_list_free(t_token *head);
void	token_no_content_free(t_token *head);
void	tree_free(t_tree *tree);
void	tree_node_free(char **node);
void	envp_free(t_envp **envp);
void	envp_char_free(char ***envp);
void	split_free(char **split);

// envp function
t_envp	*create_envp_table(char **envp);

//Execution
int execution(t_tree *tree, t_envp *envp, int *fd);
int	redirect(t_tree **tree, int *fd);
<<<<<<< HEAD

// Lexer functions
void	debug_lexer(t_token *list);
char	***lexer(char *input, t_tokens_type **signals_ptr, t_check *flags);
void	ft_skip_spaces(char *input, int *index);
int		ft_isspace(char c);
=======
>>>>>>> a76e4aea5fd1080f9663ce9d49c28cc9e40b9b33

#endif
