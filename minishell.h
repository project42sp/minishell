/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:16:10 by buehara           #+#    #+#             */
/*   Updated: 2026/02/12 19:18:03 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"


typedef struct	s_tree{
	void	*node;
	t_tree	*left;
	t_tree	*right;
}	t_tree;

