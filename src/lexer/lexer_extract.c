/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:05:30 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/03 12:37:57 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_quote_char(char *input, int *i, char *quote)
{
	if (*quote == 0 && (input[*i] == '"' || input[*i] == '\''))
	{
		*quote = input[*i];
		(*i)++;
	}
	else if (*quote != 0 && input[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
	}
	else
		(*i)++;
}

static int	skip_word(char *input, int *i)
{
	char	quote;
	int		start;

	start = *i;
	quote = 0;
	while (input[*i] != '\0')
	{
		if (quote != 0 || (input[*i] == '"' || input[*i] == '\''))
			handle_quote_char(input, i, &quote);
		else if (ft_isspace(input[*i]) || get_operator_type(input + *i) != CMD)
			break ;
		else
			(*i)++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (1);
	}
	return (0);
}

static char	*collect_word(char *input, int *i)
{
	int		start;
	char	*result;

	start = *i;
	if (skip_word(input, i) != 0)
		return (NULL);
	result = ft_substr(input, start, *i - start);
	return (result);
}

char	*extract_token(char *input, int *i, t_tokens_type *type)
{
	char	*word;

	if (handle_operator(input, i, type))
		return (NULL);
	word = collect_word(input, i);
	if (word && type)
		*type = CMD;
	return (word);
}
