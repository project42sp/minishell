/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:46:52 by thfernan          #+#    #+#             */
/*   Updated: 2026/06/04 03:59:40 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redir(t_token *current, t_token *next)
{
	if (!is_redir(current->signal))
		return (1);
	if (!next || next->signal == EOFILE
		|| (next->signal != FILE_PATH && next->signal != CMD))
		return (syntax_error(current));
	return (1);
}

static int	check_control_op(t_token *current, t_token *next)
{
	if (!is_pipe_logical(current->signal))
		return (1);
	if (!next || next->signal == EOFILE)
		return (syntax_error(current));
	if (is_pipe_logical(next->signal))
		return (syntax_error(current));
	return (1);
}

static int	check_consecutive_redirs(t_token *previous, t_token *current)
{
	if (previous && is_redir(previous->signal) && is_redir(current->signal))
		return (syntax_error(current));
	return (1);
}

static int	check_last_token(t_token *previous)
{
	if (previous && (is_redir(previous->signal)
			|| is_pipe_logical(previous->signal)))
		return (syntax_error(previous));
	return (1);
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
		if (!previous && is_pipe_logical(current->signal))
			return (syntax_error(current));
		if (!check_redir(current, next))
			return (0);
		if (!check_control_op(current, next))
			return (0);
		if (!check_consecutive_redirs(previous, current))
			return (0);
		previous = current;
		current = current->next;
	}
	return (check_last_token(previous));
}
