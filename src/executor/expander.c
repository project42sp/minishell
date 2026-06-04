/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:20:49 by thfernan          #+#    #+#             */
/*   Updated: 2026/06/04 16:07:04 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*safe_strjoin(char *s1, char *s2)
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

char	*envp_get_value(t_envp *envp, char *key)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	update_exit_status(t_envp *envp, int status)
{
	char	*str;

	while (envp)
	{
		if (ft_strcmp(envp->key, "?") == 0)
		{
			free(envp->value);
			str = ft_itoa(status);
			envp->value = str;
			return ;
		}
		envp = envp->next;
	}
}

static char	*append_char(char *result, char c)
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

static char	*handle_dollar(char *result, char *str, int *i, t_envp *envp)
{
	char	*value;
	char	*var_name;
	int		start;
	int		j;

	if (str[*i + 1] == '?')
	{
		value = envp_get_value(envp, "?");
		if (value)
			result = safe_strjoin(result, value);
		*i += 2;
		return (result);
	}
	if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
	{
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
	result = append_char(result, '$');
	(*i)++;
	return (result);
}

static char	*handle_backslash(char *result, char *str, int *i, int in_double)
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

char	*expand_argument(char *arg, t_envp *envp)
{
	char	*result;
	int		i;
	int		in_single;
	int		in_double;

	if (!arg)
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (arg[i])
	{
		if (!in_single && arg[i] == '"')
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		if (!in_double && arg[i] == '\'')
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		if (in_single)
		{
			result = append_char(result, arg[i]);
			i++;
			continue ;
		}
		if (arg[i] == '\\')
		{
			result = handle_backslash(result, arg, &i, in_double);
			if (!result)
				return (NULL);
			continue ;
		}
		if (arg[i] == '$')
		{
			result = handle_dollar(result, arg, &i, envp);
			if (!result)
				return (NULL);
			continue ;
		}
		result = append_char(result, arg[i]);
		i++;
	}
	return (result);
}

void expand_tree_args(t_tree *tree, t_envp *envp)
{
	int		i;
	char	**argv;
	char	*expanded;

	if (!tree)
		return;
	expand_tree_args(tree->left, envp);
	expand_tree_args(tree->right, envp);
	if (tree->signal == CMD)
	{
		argv = (char **)tree->node;
		if (!argv)
			return;
		i = 0;
		while (argv[i])
		{
			expanded = expand_argument(argv[i], envp);
			if (expanded)
			{
				free(argv[i]);
				argv[i] = expanded;
			}
			i++;
		}
	}
}
