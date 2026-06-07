/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:41:16 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/03 13:44:53 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_token(t_token **head, t_token **last, t_token *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*last)->next = new_node;
	*last = new_node;
}

static void	init_lexer(t_lexer *data, t_check *flags)
{
	data->head = NULL;
	data->tail = NULL;
	data->i = 0;
	data->last_type = EOFILE;
	data->flags = flags;
	ft_bzero(flags, sizeof(t_check));
}

static int	process_token(char *input, t_lexer *data)
{
	char			*content;
	t_tokens_type	token_type;
	t_token			*new_node;

	token_type = 0;
	content = extract_token(input, &data->i, &token_type);
	if (token_type == CMD && content == NULL)
	{
		token_list_free(data->head);
		return (0);
	}
	if (token_type == CMD && (data->last_type >= INPUT
			&& data->last_type <= HEREDOC))
		token_type = FILE_PATH;
	update_flags(data->flags, token_type);
	new_node = token_node(content, token_type);
	if (!new_node)
	{
		free(content);
		token_free_partial(data->head, NULL);
		return (0);
	}
	append_token(&data->head, &data->tail, new_node);
	data->last_type = token_type;
	return (1);
}

static int	add_eof_token(t_lexer *data)
{
	t_token	*eof_node;

	eof_node = token_node(NULL, EOFILE);
	if (!eof_node)
	{
		token_free_partial(data->head, NULL);
		return (0);
	}
	append_token(&data->head, &data->tail, eof_node);
	return (1);
}

t_token	*lexer(char *input, t_check *flags)
{
	t_lexer	data;

	init_lexer(&data, flags);
	while (1)
	{
		ft_skip_spaces(input, &data.i);
		if (!input[data.i])
			break ;
		if (!process_token(input, &data))
			return (NULL);
	}
	if (!add_eof_token(&data))
		return (NULL);
	return (data.head);
}
