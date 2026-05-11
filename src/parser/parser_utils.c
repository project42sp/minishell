/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:57:26 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/09 15:01:00 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(t_tokens_type type)
{
	int	result;

	result = 0;
	if (type >= INPUT && type <= HEREDOC)
		result = 1;
	return (result);
}

int	is_pipe_logical(t_tokens_type type)
{
	int	result;

	result = 0;
	if (type == PIPE || type == AND || type == OR)
		result = 1;
	return (result);
}

int	syntax_error(t_token *token)
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
