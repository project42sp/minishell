/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 04:00:27 by buehara           #+#    #+#             */
/*   Updated: 2026/06/04 04:00:29 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	check_signal_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa_int;

	g_signal = 0;
	rl_event_hook = check_signal_hook;
	sa_int.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
}
