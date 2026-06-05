/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:23:26 by thfernan          #+#    #+#             */
/*   Updated: 2026/06/05 05:26:31 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_temp_path_name(char *eof, int index)
{
	char	*name_pid;
	char	*name_index;
	char	*pid;
	char	*index_char;

	pid = ft_itoa(getpid());
	if (!pid)
		return (NULL);
	name_pid = ft_strjoin(eof, pid);
	free(pid);
	if (!name_pid)
		return (NULL);
	index_char = ft_itoa(index);
	if (!index_char)
	{
		free(name_pid);
		return (NULL);
	}
	name_index = ft_strjoin(name_pid, index_char);
	free(index_char);
	free(name_pid);
	if (!name_index)
		return (NULL);
	return (name_index);
}

char	**create_temp_file(char *eof, int index, int *fd)
{
	char	*file;
	char	*full_path;
	char	**file_node;

	file = create_temp_path_name(eof, index);
	if (!file)
		return (NULL);
	full_path = ft_strjoin("/tmp/.", file);
	free(file);
	if (!full_path)
		return (NULL);
	*fd = open(full_path, O_RDWR | O_CREAT, 0600);
	if (*fd == -1)
	{
		free(full_path);
		return (NULL);
	}
	file_node = (char **)ft_calloc(sizeof(char *), 2);
	if (!file_node)
	{
		free(full_path);
		return (NULL);
	}
	file_node[0] = full_path;
	return (file_node);
}
