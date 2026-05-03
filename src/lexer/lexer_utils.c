/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:57:38 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/03 11:57:38 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\r' || c == '\f');
}

void	ft_skip_spaces(char *input, int *index)
{
	while (input[*index] && ft_isspace(input[*index]))
		(*index)++;
}

void	update_flags(t_check *flags, t_tokens_type type)
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
