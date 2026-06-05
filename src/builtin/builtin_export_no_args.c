/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 18:06:43 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 12:14:02 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_keys(t_envp **envp)
{
	int	count;

	if (!envp)
		return (0);
	count = 0;
	while (envp[count])
	{
		count++;
	}
	return (count);
}

static t_envp	**create_list(t_envp *envp)
{
	int		size;
	int		index;
	t_envp	**list;
	t_envp	*temp;

	if (!envp)
		return (NULL);
	size = envp_len(envp);
	list = (t_envp **)ft_calloc(sizeof(t_envp *), size + 1);
	if (!list)
		return (NULL);
	temp = envp;
	index = 0;
	while (index < size)
	{
		list[index] = temp;
		temp = temp->next;
		index++;
	}
	return (list);
}

static t_envp	**envp_reorder(t_envp **envp)
{
	int		size;
	int		inner;
	int		out;
	t_envp	*key;

	if (!envp)
		return (NULL);
	size = count_keys(envp);
	out = 1;
	while (out < size)
	{
		inner = out - 1;
		key = envp[out];
		while (inner >= 0
			&& ft_strncmp(envp[inner]->key, key->key,
				ft_strlen(envp[inner]->key)) > 0)
		{
			envp[inner + 1] = envp[inner];
			inner--;
		}
		envp[inner + 1] = key;
		out++;
	}
	return (envp);
}

static void	print_export(t_envp **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strcmp(envp[index]->key, "?") == 0)
		{
			index++;
			continue ;
		}
		ft_printf("declare\t-x ");
		ft_printf("%s", envp[index]->key);
		if (envp[index]->flag == ENV)
		{
			ft_printf("=");
			if (envp[index]->value)
				ft_printf("\"%s\"", envp[index]->value);
			else
				ft_printf("\"\"");
		}
		ft_printf("\n");
		index++;
	}
}

int	export_empty(t_envp **envp)
{
	t_envp	**list;

	list = create_list(*envp);
	if (!list)
		return (1);
	list = envp_reorder(list);
	if (!list)
	{
		free(list);
		return (1);
	}
	print_export(list);
	free(list);
	return (0);
}
