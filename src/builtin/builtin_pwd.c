/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:52:45 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 14:52:46 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	int		size;
	char	*buf;

	size = 4096;
	buf = NULL;
	buf = getcwd(buf, size);
	if (!buf)
		return (2);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}
