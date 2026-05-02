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
void	tokens_print(t_token *token);

// Token Create Functions
t_tree	*tree_create(t_token *list, t_check *flags);
t_token	*token_node(char *token_str, t_tokens_type signal);
t_token	*get_next_token(t_token *token);

// Free functions
void	token_list_free(t_token *head);
void	token_free_partial(t_token *head, t_token *limit);
void	tree_free(t_tree **tree);
void	tree_node_free(char **node);
void	envp_free(t_envp **envp);
void	envp_char_free(char ***envp);
void	split_free(char **split);

// envp function
t_envp	*create_envp_table(char **envp);
char	**envp_rebuilt(t_envp *envp_table);

//Execution
int		execution(t_tree *tree, t_envp *envp_table);
int		redirect(t_tree **tree, int *fd);
char	**create_path_table(t_envp *envp);
char	*find_path(char **path_envp, char **cmd);

// Lexer functions
void	debug_lexer(t_token *list);
t_token	*lexer(char *input, t_check *flags);
void	ft_skip_spaces(char *input, int *index);
int		ft_isspace(char c);

// Parser functions
t_tree	*parser(char *input);

#endif
