#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tokens_type
{
	CMD,
	FILE_PATH,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	EOFILE
}	t_tokens_type;

typedef struct e_tk_check
{
	int	word;
	int	input;
	int	output;
	int	pipe;
	int	logical;
}	t_check;

typedef struct e_token
{
	t_tokens_type		signal;
	void				*token;
	struct e_token		*next;
}	t_token;

#endif
