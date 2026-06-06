/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:46:44 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/09 14:46:45 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*parser(char *input)
{
	t_check			flags;
	t_token			*tokens;
	t_tree			*tree;

	ft_bzero(&flags, sizeof(t_check));
	tokens = lexer(input, &flags);
	if (!tokens)
	{
		ft_printf("Lexer error: invalid syntax\n");
		return (NULL);
	}
	if (!validate_syntax(tokens))
	{
		token_list_free(tokens);
		return (NULL);
	}
	tokens_print(tokens);
	tokens = token_cmd_reorder(tokens);
	tokens_print(tokens);
	tree = tree_create(tokens, &flags);
	tree_print(tree, 0);
	tree_print_extense(tree);
	printf("\n\n");
	token_list_free(tokens);
	return (tree);
}
