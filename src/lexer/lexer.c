#include "../includes/minishell.h"

static int	count_tokens(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '<' || input[i] == '>')
		{
			count++;
			i++;
			if (input[i] == '<' || input[i] == '>')
				i++;
		}
		else if (input[i] == '|')
		{
			count++;
			i++;
			if (input[i] == '|')
				i++;
		}
		else if (input[i] == '&' && input[i + 1] == '&')
		{
			count++;
			i += 2;
		}
		else
		{
			count++;
			while (input[i] && input[i] != ' '
				&& input[i] != '|' && input[i] != '<'
				&& input[i] != '>' && input[i] != '&')
				i++;
		}
	}
	return (count);
}

static t_tokens_type	get_signal(char *token)
{
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(token, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(token, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(token, "<", 1) == 0)
		return (INPUT);
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUTPUT);
	return (CMD);
}

static char	*get_token(char *input, int *i)
{
	int		start;

	while (input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		(*i)++;
		if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
			(*i)++;
	}
	else if (input[*i] == '&' && input[*i + 1] == '&')
		(*i) += 2;
	else
	{
		while (input[*i] && input[*i] != ' '
			&& input[*i] != '|' && input[*i] != '<'
			&& input[*i] != '>' && input[*i] != '&')
			(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

t_token	*lexer(char *input, t_check *flags)
{
	char			***tokens;
	t_tokens_type	*signals;
	t_token			*list;
	int				count;
	int				i;
	int				j;

	count = count_tokens(input);
	tokens = (char ***)ft_calloc(count + 2, sizeof(char **));
	signals = (t_tokens_type *)ft_calloc(count + 2, sizeof(t_tokens_type));
	if (!tokens || !signals)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		tokens[j] = (char **)ft_calloc(2, sizeof(char *));
		if (!tokens[j])
		{
			while (j > 0)
			{
				j--;
				free(tokens[j][0]);
				free(tokens[j]);
			}
			free(tokens);
			free(signals);
			return (NULL);
		}
		tokens[j][0] = get_token(input, &i);
		tokens[j][1] = NULL;
		if (!tokens[j][0])
		{
			free(tokens[j]);
			while (j > 0)
			{
				j--;
				free(tokens[j][0]);
				free(tokens[j]);
			}
			free(tokens);
			free(signals);
			return (NULL);
		}
		signals[j] = get_signal(tokens[j][0]);
		if (signals[j] == INPUT || signals[j] == OUTPUT
			|| signals[j] == HEREDOC || signals[j] == APPEND)
		{
			flags->input += (signals[j] == INPUT || signals[j] == HEREDOC);
			flags->output += (signals[j] == OUTPUT || signals[j] == APPEND);
			j++;
			tokens[j] = (char **)ft_calloc(2, sizeof(char *));
			if (!tokens[j])
			{
				while (j > 0)
				{
					j--;
					free(tokens[j][0]);
					free(tokens[j]);
				}
				free(tokens);
				free(signals);
				return (NULL);
			}
			tokens[j][0] = get_token(input, &i);
			tokens[j][1] = NULL;
			if (!tokens[j][0])
			{
				free(tokens[j]);
				while (j > 0)
				{
					j--;
					free(tokens[j][0]);
					free(tokens[j]);
				}
				free(tokens);
				free(signals);
				return (NULL);
			}
			signals[j] = FILE_PATH;
			j++;
		}
		else
		{
			if (signals[j] == PIPE)
				flags->pipe = 1;
			else if (signals[j] == AND || signals[j] == OR)
				flags->logical = 1;
			else
				flags->word = 1;
			j++;
		}
	}
	tokens[j] = NULL;
	signals[j] = EOFILE;
	j = 0;
	while (j < count)
	{
		if (signals[j] == PIPE || signals[j] == AND || signals[j] == OR
			|| signals[j] == INPUT || signals[j] == OUTPUT
			|| signals[j] == APPEND || signals[j] == HEREDOC)
		{
			free(tokens[j][0]);
			free(tokens[j]);
			tokens[j] = NULL;
		}
		j++;
	}
	list = token_create(tokens, signals);
	free(tokens);
	free(signals);
	return (list);
}

void	debug_lexer(t_token *list)
{
	t_token	*curr;
	char	*types[] = {
		"CMD", "FILE_PATH", "INPUT", "OUTPUT",
		"APPEND", "HEREDOC", "PIPE", "AND", "OR", "EOFILE"
	};
	char	*symbols[] = {
		"", "", "<", ">", ">>", "<<", "|", "&&", "||", ""
	};

	ft_printf("\n=== LEXER DEBUG ===\n");
	curr = list;
	while (curr)
	{
		if (curr->token)
			ft_printf("[%-9s] \"%s\"\n", types[curr->signal],
				((char **)curr->token)[0]);
		else
			ft_printf("[%-9s] \"%s\"\n", types[curr->signal],
				symbols[curr->signal]);
		curr = curr->next;
	}
	ft_printf("===================\n\n");
}