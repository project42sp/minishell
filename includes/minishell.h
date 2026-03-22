#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef struct s_tree
{
	void			*node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

#endif
