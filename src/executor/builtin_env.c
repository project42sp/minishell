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

int	ft_env(t_envp *envp)
{
	t_envp	*head;
	char	*value;

	head = envp;
	while (head)
	{
		value = head->value;
		if (!value)
			value = "";
		ft_printf("%s=%s\n", head->key, value);
		head = head->next;
	}
	return (0);
}
