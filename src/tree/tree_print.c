/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfernan <thfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:23:58 by buehara           #+#    #+#             */
/*   Updated: 2026/05/24 17:44:21 by thfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <strings.h>

void	tree_print(t_tree *tree, int level)
{
	if (!tree)
		return ;
	tree_print(tree->right, level + 1);
	if (tree && tree->node)
		printf("%*c%s\n", level * 5, ' ', ((char **)tree->node)[0]);
	else
		switch (tree->signal) {
			case INPUT: printf("%*c<\n", level * 5, ' '); break;
			case OUTPUT: printf("%*c>\n", level * 5, ' '); break;
			case APPEND: printf("%*c>>\n", level * 5, ' '); break;
			case HEREDOC: printf("%*c<<\n", level * 5, ' '); break;
			case PIPE: printf("%*c | \n", level * 5, ' '); break;
			default:
				printf(" ");
		}
	tree_print(tree->left, level + 1);
}

void	tree_print_extense(t_tree *tree)
{
	if (!tree)
		return ;
	tree_print_extense(tree->left);
	if (tree && tree->node)
	{
		switch (tree->signal) {
			case CMD: printf(" CMD "); break;
			case FILE_PATH: printf(" FILE "); break;
		}
		printf(" %s ", ((char **)tree->node)[0]);
	}
	else if (tree)
		switch (tree->signal) {
			case INPUT: printf(" < "); break;
			case OUTPUT: printf(" > "); break;
			case APPEND: printf(" >> "); break;
			case HEREDOC: printf(" << "); break;
			case PIPE: printf(" | "); break;
			default:
				printf(" ");
		}
	tree_print_extense(tree->right);
}

void	tokens_print(t_token *token)
{
	t_token	*head;
	char	**temp;
	int		index;

	head = token;
	if (!token)
		return ;
	while (head)
	{
		if (head->token)
		{
			switch (head->signal) {
				case CMD: ft_printf(" CMD "); break;
				case FILE_PATH: ft_printf(" FILE "); break;
				default: ft_printf(" ");
			}
			temp = (char **)token->token;
			index = 0;
			while (temp && temp[index] != NULL)
			{
				ft_printf("%s  ", temp[index]);
				index++;
			}
		}
		else if (head)
			switch (head->signal) {
				case INPUT: ft_printf(" < "); break;
				case OUTPUT: ft_printf(" > "); break;
				case APPEND: ft_printf(" >> "); break;
				case HEREDOC: ft_printf(" << "); break;
				case PIPE: ft_printf(" | "); break;
				default:
					ft_printf(" ");
			}
		head = head->next;
	}
	ft_printf("\n");
}
