#include "../../includes/minishell.h"

static int	is_redir(t_tokens_type type)
{
	int	result;

	result = 0;
	if (type >= INPUT && type <= HEREDOC)
		result = 1;
	return (result);
}

static int	is_pipe_logical(t_tokens_type type)
{
	int	result;

	result = 0;
	if (type == PIPE || type == AND || type == OR)
		result = 1;
	return (result);
}

static int	syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token->signal == EOFILE)
		ft_putstr_fd("newline", 2);
	else if (token->token)
		ft_putstr_fd(((char **)token->token)[0], 2);
	else
		ft_putstr_fd((char *)get_operator_symbol(token->signal), 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*previous;
	t_token	*next;

	current = tokens;
	previous = NULL;
	while (current && current->signal != EOFILE)
	{
		next = current->next;
		// Token nao pode ser operador de controle (pipe e logicos)
		if (!previous && is_pipe_logical(current->signal))
			return (syntax_error(current));
		// Redirecionador deve ser seguido por FILE_PATH ou CMD como arquivo
		if (is_redir(current->signal))
		{
			if (!next || next->signal == EOFILE
				|| (next->signal != FILE_PATH && next->signal != CMD))
				return (syntax_error(current));
		}
		// Operador de controle deve ter comando dos dois lados
		if (is_pipe_logical(current->signal))
		{
			if (!next || next->signal == EOFILE
				|| is_pipe_logical(next->signal))
				return (syntax_error(current));
		}
		// Redirecionadores consecutivos sem arquivo no meio (ex: > <)
		if (previous && is_redir(previous->signal) && is_redir(current->signal))
			return (syntax_error(current));
		previous = current;
		current = current->next;
	}
	// Último token (antes de EOFILE) não pode ser operador
	if (previous && (is_redir(previous->signal)
			|| is_pipe_logical(previous->signal)))
		return (syntax_error(previous));
	return (1);
}
