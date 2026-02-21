/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:16:10 by buehara           #+#    #+#             */
/*   Updated: 2026/02/21 16:32:46 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_AND,
	NODE_OR,
}	t_node_type;

typedef struct s_tree
{
	void	*node;
	t_tree	*left;
	t_tree	*right;
}	t_tree;

#endif
