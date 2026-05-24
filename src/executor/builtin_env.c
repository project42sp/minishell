/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 10:22:03 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 10:22:04 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		ft_printf("%s\n", envp[index]);
		index++;
	}
	return (0);
}
