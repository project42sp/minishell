#ifndef TOKEN_H
# define TOKEN_H

#include "minishell.h"

typedef enum e_tokens_type
{
	CMD,
	FILE_PATH,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	AND,
	OR,
	EOFILE
}	t_tokens_type;

typedef struct e_token
{
	t_tokens_type		signal;
	void				*token;
	struct e_token_list	*next;
}	t_token;

#endif
