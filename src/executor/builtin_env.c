/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 10:22:03 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 12:12:57 by thfernan         ###   ########.fr       */
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
		if (ft_strcmp(head->key, "?") == 0)
		{
			head = head->next;
			continue ;
		}
		value = head->value;
		if (!value)
			value = "";
		ft_printf("%s=%s\n", head->key, value);
		head = head->next;
	}
	return (0);
}
