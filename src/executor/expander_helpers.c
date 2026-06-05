/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:02:47 by thfernan          #+#    #+#             */
/*   Updated: 2026/06/05 02:25:45 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*safe_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*append_char(char *result, char c)
{
	char	*temp;

	if (!result)
		result = ft_strdup("");
	if (!result)
		return (NULL);
	temp = malloc(2);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	temp[0] = c;
	temp[1] = '\0';
	result = safe_strjoin(result, temp);
	free(temp);
	return (result);
}

static char	*handle_dollar_variable(char *result, char *str, int *i,
			t_envp *envp)
{
	char	*value;
	char	*var_name;
	int		start;
	int		j;

	start = *i + 1;
	j = start;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, start, j - start);
	if (!var_name)
	{
		free(result);
		return (NULL);
	}
	value = envp_get_value(envp, var_name);
	if (value)
		result = safe_strjoin(result, value);
	free(var_name);
	*i = j;
	return (result);
}

char	*handle_dollar(char *result, char *str, int *i, t_envp *envp)
{
	char	*value;

	if (str[*i + 1] == '?')
	{
		value = envp_get_value(envp, "?");
		if (value)
			result = safe_strjoin(result, value);
		*i += 2;
		return (result);
	}
	if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
		return (handle_dollar_variable(result, str, i, envp));
	result = append_char(result, '$');
	(*i)++;
	return (result);
}

char	*handle_backslash(char *result, char *str, int *i, int in_double)
{
	char	c;

	(*i)++;
	if (str[*i] == '\0')
		return (result);
	if (in_double)
	{
		c = str[*i];
		if (c == '$' || c == '"' || c == '\\' || c == '`' || c == '\n')
			result = append_char(result, c);
		else
		{
			result = append_char(result, '\\');
			if (result)
				result = append_char(result, c);
		}
	}
	else
		result = append_char(result, str[*i]);
	(*i)++;
	return (result);
}
