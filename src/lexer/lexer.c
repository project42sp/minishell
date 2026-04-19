#include "../includes/minishell.h"

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

static int	count_tokens(char *input)
{
	int		i;
	int		count;
	char	*temp;

	i = 0;
	count = 0;
	while (1)
	{
		temp = extract_token(input, &i, NULL);
		if (!temp && !input[i])
			break ;
		if (temp)
			free(temp);
		count++;
	}
	return (count);
}

char ***lexer(char *input, t_tokens_type **signals_ptr, t_check *flags)
{
	char			***tokens;
	t_tokens_type 	*signals;
	int				count;
	int				i;
	int				j;
	t_tokens_type	last_type;
	char			*token_str;
	t_tokens_type	token_type;

	if (!input || !flags)
		return (NULL);
	ft_bzero(flags, sizeof(t_check));
	count = count_tokens(input);
	tokens = ft_calloc(count + 2, sizeof(char **));
	signals = ft_calloc(count + 2, sizeof(t_tokens_type));
	if (!tokens || !signals)
		return (NULL);
	i = 0;
	j = 0;
	last_type = EOFILE;
	while (j < count)
	{
		tokens[j] = ft_calloc(2, sizeof(char *));
		if (!tokens[j])
		{
			while (j > 0)
			{
				free(tokens[j - 1][0]);
				free(tokens[j - 1]);
				j--;
			}
			free(tokens);
			free(signals);
			return (NULL);
		}
		token_str = extract_token(input, &i, &token_type);
		tokens[j][0] = token_str;
		tokens[j][1] = NULL;
		if (token_str == NULL)
			signals[j] = token_type;
		else
		{
			if (last_type >= INPUT && last_type <= HEREDOC)
				signals[j] = FILE_PATH;
			else
				signals[j] = CMD;
		}
		if (signals[j] == PIPE)
			flags->pipe = 1;
		else if (signals[j] == AND || signals[j] == OR)
			flags->logical = 1;
		else if (signals[j] == INPUT || signals[j] == HEREDOC)
			flags->input = 1;
		else if (signals[j] == OUTPUT || signals[j] == APPEND)
			flags->output = 1;
		else if (signals[j] == CMD || signals[j] == FILE_PATH)
			flags->word = 1;
		last_type = signals[j];
		j++;
	}
	tokens[j] = NULL;
	signals[j] = EOFILE;
	*signals_ptr = signals;
	return (tokens);
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
		// Verifica se há uma string válida
		if (curr->token && ((char **)curr->token)[0] != NULL)
			ft_printf("\"%s\"\n", ((char **)curr->token)[0]);
		else
			ft_printf("symbol=\"%s\"\n", get_operator_symbol(curr->signal));
		curr = curr->next;
	}
	ft_printf("===================\n\n");
}