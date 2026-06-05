/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:20:49 by thfernan          #+#    #+#             */
/*   Updated: 2026/06/05 02:25:26 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	process_char(t_expand *state, char *arg, t_envp *envp)
{
	if (!state->in_single && arg[state->i] == '"')
		state->in_double = !state->in_double;
	else if (!state->in_double && arg[state->i] == '\'')
		state->in_single = !state->in_single;
	else if (state->in_single)
		state->result = append_char(state->result, arg[state->i]);
	else if (arg[state->i] == '\\')
		state->result = handle_backslash(state->result, arg, &state->i,
				state->in_double);
	else if (arg[state->i] == '$')
		state->result = handle_dollar(state->result, arg, &state->i, envp);
	else
		state->result = append_char(state->result, arg[state->i]);
	if (!state->result)
		return (0);
	if (arg[state->i] && arg[state->i] != '\\' && arg[state->i] != '$')
		state->i++;
	return (1);
}

char	*expand_argument(char *arg, t_envp *envp)
{
	t_expand	state;

	if (!arg)
		return (ft_strdup(""));
	state.result = ft_strdup("");
	if (!state.result)
		return (NULL);
	state.i = 0;
	state.in_single = 0;
	state.in_double = 0;
	while (arg[state.i] && process_char(&state, arg, envp))
		continue ;
	return (state.result);
}

void	expand_tree_args(t_tree *tree, t_envp *envp)
{
	int		i;
	char	**argv;
	char	*expanded;

	if (!tree)
		return ;
	expand_tree_args(tree->left, envp);
	expand_tree_args(tree->right, envp);
	if (tree->signal == CMD)
	{
		argv = (char **)tree->node;
		if (!argv)
			return ;
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
