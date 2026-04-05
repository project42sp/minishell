/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:16:10 by buehara           #+#    #+#             */
/*   Updated: 2026/04/05 15:29:13 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "token.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef struct s_tree
{
	int				signal;
	void			*node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//t_tree	*tree_node_create(t_tree *left, void *token, t_tree *right);
void	tree_print(t_tree *tree, int level);
void	tree_print_extense(t_tree *tree);

t_tree	*tree_create(t_token *list, t_check *flags);
t_token	*token_create(char ***tokens, t_tokens_type *signal);
t_token	*get_next_token(t_token *token);

void	tree_print_extense(t_tree *tree);

// Free functions
void	token_list_free(t_token *head);
void	token_no_content_free(t_token *head);
void	tree_free(t_tree *tree);

// Lexer functions
void		debug_lexer(t_token *list);
t_token		*lexer(char *input, t_check *flags);

#endif
