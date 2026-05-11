/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:46:31 by thfernan          #+#    #+#             */
/*   Updated: 2026/05/09 14:46:32 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**add_arg(char **argv, char *new_str, int count)
{
	char	**new_argv;
	int		i;

	new_argv = ft_calloc(count + 2, sizeof(char *));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[count] = new_str;
	new_argv[count + 1] = NULL;
	free(argv);
	return (new_argv);
}

char	**collect_args(t_token **token)
{
	char	**argv;
	int		count;
	char	*str;

	argv = NULL;
	count = 0;
	while (*token && (*token)->signal == CMD)
	{
		str = ((char **)(*token)->token)[0];
		argv = add_arg(argv, str, count);
		if (!argv)
			return (NULL);
		((char **)(*token)->token)[0] = NULL;
		*token = (*token)->next;
		count++;
	}
	if (count == 0)
		argv = ft_calloc(1, sizeof(char *));
	return (argv);
}
