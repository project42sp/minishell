/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:58:37 by thfernan          #+#    #+#             */
/*   Updated: 2026/02/21 16:43:46 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	t_tree	*ast;
	int		status;

	ast = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			//add_history(line);
			ast = update_tree(ast, line);
			if (ast)
				status = read_tree(ast);
		}
		free(line);
	}
	free_tree(ast);
}
