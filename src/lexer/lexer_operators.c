/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:57:49 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/09 09:19:30 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	operator_len(t_tokens_type type)
{
	if (type == HEREDOC || type == APPEND || type == OR || type == AND)
		return (2);
	if (type == PIPE || type == INPUT || type == OUTPUT)
		return (1);
	return (0);
}

t_tokens_type	get_operator_type(char *str)
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

const char	*get_operator_symbol(t_tokens_type type)
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

int	handle_operator(char *input, int *i, t_tokens_type *type)
{
	t_tokens_type	op_type;

	op_type = get_operator_type(input + *i);
	if (op_type != CMD)
	{
		if (type)
			*type = op_type;
		*i += operator_len(op_type);
		return (1);
	}
	return (0);
}
