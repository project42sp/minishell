#include "../includes/minishell.h"

// Mover pra libft
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f');
}

void	ft_skip_spaces(char *input, int *index)
{
	while (input[*index] && ft_isspace(input[*index]))
		(*index)++;
}