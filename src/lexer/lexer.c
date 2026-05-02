#include "../../includes/minishell.h"

static void	append_token(t_token **head, t_token **last, t_token *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*last)->next = new_node;
	*last = new_node;
}
static int	operator_len(t_tokens_type type)
{
	if (type == HEREDOC || type == APPEND || type == OR || type == AND)
		return (2);
	if (type == PIPE || type == INPUT || type == OUTPUT)
		return (1);
	return (0);
}

static t_tokens_type	get_operator_type(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	if (*str == '|')
		return (PIPE);
	if (*str == '<')
		return (INPUT);
	if (*str == '>')
		return (OUTPUT);
	return (CMD);
}

static char	*extract_token(char *input, int *i, t_tokens_type *type)
{
	int				start;
	char			quote;
	t_tokens_type	op_type;

	ft_skip_spaces(input, i);
	if (!input[*i])
		return (NULL);
	op_type = get_operator_type(input + *i);
	if (op_type != CMD)
	{
		if (type)
			*type = op_type;
		*i += operator_len(op_type);
		return(NULL);
	}
	start = *i;
	quote = 0;
	while (input[*i])
	{
		if (quote == 0 && (input[*i] == '"' || input[*i] == '\''))
		{
			quote = input[*i];
			(*i)++;
			continue ;
		}
		if (quote != 0 && input[*i] == quote)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if (quote != 0)
		{
			(*i)++;
			continue ;
		}
		if (ft_isspace(input[*i]))
			break ;
		if (get_operator_type(input + *i) != CMD)
			break ;
		(*i)++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	if (type)
		*type = CMD;
	return (ft_substr(input, start, *i - start));
}

static const char *get_operator_symbol(t_tokens_type type)
{
	if (type == INPUT)
		return ("<");
	if (type == OUTPUT)
		return (">");
	if (type == APPEND)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	if (type == PIPE)
		return ("|");
	if (type == AND)
		return ("&&");
	if (type == OR)
		return ("||");
	return ("");
}

static void	update_flags(t_check *flags, t_tokens_type type)
{
	if (type == PIPE)
		flags->pipe = 1;
	else if (type == AND || type == OR)
		flags->logical = 1;
	else if (type == INPUT || type == HEREDOC)
		flags->input = 1;
	else if (type == OUTPUT || type == APPEND)
		flags->output = 1;
	else if (type == CMD || type == FILE_PATH)
		flags->word = 1;
}

t_token *lexer(char *input, t_check *flags)
{
	t_token			*head;
	t_token			*tail;
	t_token			*new_node;
	t_token			*eof_node;
	char			*content;
	int				i;
	t_tokens_type	last_type;
	t_tokens_type	token_type;

	head = NULL;
	tail = NULL;
	i = 0;
	last_type = EOFILE;
	ft_bzero(flags, sizeof(t_check));
	while (1)
	{
		ft_skip_spaces(input, &i);
		if (!input[i])
			break ;
		content = extract_token(input, &i, &token_type);
		if (token_type == CMD && content == NULL)
		{
			token_free_partial(head, NULL);
			return (NULL);
		}
		if (token_type == CMD && (last_type >= INPUT && last_type <= HEREDOC))
			token_type = FILE_PATH;
		update_flags(flags, token_type);
		new_node = token_node(content, token_type);
		if (!new_node)
		{
			free(content);
			token_free_partial(head, NULL);
			return (NULL);
		}
		append_token(&head, &tail, new_node);
		last_type = token_type;
	}
	eof_node = token_node(NULL, EOFILE);
	if (!eof_node)
	{
		token_free_partial(head, NULL);
		return (NULL);
	}
	append_token(&head, &tail, eof_node);
	return (head);
}

void debug_lexer(t_token *list)
{
	t_token		*curr;
	const char	*types[] = {
		"CMD", "FILE_PATH", "INPUT", "OUTPUT",
		"APPEND", "HEREDOC", "PIPE", "AND", "OR", "EOFILE"
	};

	ft_printf("\n=== LEXER DEBUG ===\n");
	curr = list;
	while (curr)
	{
		ft_printf("[%-9s] ", types[curr->signal]);
		if (curr->signal == EOFILE)
			ft_printf("(end of file)\n");
		else if (curr->token)
			ft_printf("\"%s\"\n", ((char **)curr->token)[0]);
		else
			ft_printf("symbol=\"%s\"\n", get_operator_symbol(curr->signal));
		curr = curr->next;
	}
	ft_printf("===================\n\n");
}
