/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:24:04 by buehara           #+#    #+#             */
/*   Updated: 2026/06/06 13:55:24 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*handle_cmd_token(t_token **token, t_tree *cmd_node)
{
	char	**argv;

	argv = collect_args(token);
	if (!argv)
		return (NULL);
	tree_free(&cmd_node);
	cmd_node = create_cmd_node(argv);
	return (tree_redir_helper(token, cmd_node));
}

t_tree	*handle_redir_token(t_token **token, t_tree *cmd_node)
{
	t_tree	*file_node;
	t_tree	*redir_node;
	t_token	*token_redir;
	t_tree	*right;

	token_redir = *token;
	*token = get_next_token(*token);
	file_node = tree_node_create(NULL, token, NULL);
	right = tree_redir_helper(token, cmd_node);
	redir_node = tree_node_create(file_node, &token_redir, right);
	return (redir_node);
}

t_token	*get_next_token(t_token *token)
{
	if (!token)
		return (NULL);
	if (token->next != NULL)
		return (token->next);
	return (token);
}

t_tree	*create_cmd_node(char **argv)
{
	t_tree	*node;
	t_token	temp_token;
	t_token	*token_ptr;

	temp_token.signal = CMD;
	temp_token.token = argv;
	temp_token.next = NULL;
	token_ptr = &temp_token;
	node = tree_node_create(NULL, &token_ptr, NULL);
	return (node);
}
