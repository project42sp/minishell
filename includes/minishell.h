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

typedef struct s_envp_path
{
	t_envp			*envp_og;
	char			**path;
	char			**envp;
}	t_envp_path;

typedef struct s_lexer
{
	t_token			*head;
	t_token			*tail;
	t_tokens_type	last_type;
	t_check			*flags;
	int				i;
}	t_lexer;

typedef struct s_fd
{
	int	fd[2];
	int	oldfd;
	int	last;
}	t_fd;

// Test Functions
void			tree_print(t_tree *tree, int level);
void			tree_print_extense(t_tree *tree);
void			tokens_print(t_token *token);

// Token & Tree Create Functions
t_tree			*tree_create(t_token *list, t_check *flags);
t_tree			*create_cmd_node(char **argv);
t_tree			*tree_node_create(t_tree *left, t_token **token, t_tree *right);
t_token			*token_node(char *token_str, t_tokens_type signal);
t_token			*get_next_token(t_token *token);

// Free functions
void			token_list_free(t_token *head);
void			token_free_partial(t_token *head, t_token *limit);
void			tree_free(t_tree **tree);
void			tree_node_free(char **node);
void			envp_free(t_envp **envp);
void			envp_char_free(char ***envp);
void			envp_path_free(t_envp_path **envps);
void			split_free(char **split);

// envp function
char			**envp_rebuilt(t_envp *envp_table);
t_envp			*create_envp_table(char **envp);

//Execution
int				execution(t_tree *tree, t_envp *envp_table);
int				redirect(t_tree **tree, t_fd *fd);
int				pipe_exec(t_envp_path *envps, t_tree *tree, int oldfd);
int				ft_wait(void);
int				base_exec(t_envp_path *envps, t_tree *tree, t_fd *fd);
void			ft_close(int fd1, int fd2, int fd3, int fd4);
char			*find_path(char **path_envp, char **cmd);
char			**create_path_table(t_envp *envp);
t_fd			*fd_create(int oldfd);
t_envp_path		*create_envp_struct(t_envp *envp);

// Lexer functions
void			debug_lexer(t_token *list); // Remover
t_token			*lexer(char *input, t_check *flags);
void			ft_skip_spaces(char *input, int *index);
int				ft_isspace(char c);
void			update_flags(t_check *flags, t_tokens_type type);
int				operator_len(t_tokens_type type);
t_tokens_type	get_operator_type(char *str);
const char		*get_operator_symbol(t_tokens_type type);
int				handle_operator(char *input, int *i, t_tokens_type *type);
char			*extract_token(char *input, int *i, t_tokens_type *type);

// Parser functions
t_tree			*parser(char *input);
int				validate_syntax(t_token *tokens);
char			**collect_args(t_token **token);
int				is_redir(t_tokens_type type);
int				is_pipe_logical(t_tokens_type type);
int				syntax_error(t_token *token);

#endif
