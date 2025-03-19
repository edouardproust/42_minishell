/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal = 0;

/**
 * Retrieves and resets the last received signal.
 */
int	get_and_reset_signal(void)
{
	sig_atomic_t	sig;

	sig = g_signal;
	g_signal = 0;
	return (sig);
}

/**
 * Handles SIGINT during minishell input (main readline).
 */
void	rl_sigint_handler(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * Handles SIGINT during heredoc input (sub-readline).
 */
void	heredoc_sigint_handler(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	close(STDIN_FILENO);
}

/**
 * Handles SIGINT during command execution.
 */
void	exec_sigint_handler(int signal)
{
	g_signal = signal;
	printf("\n");
}
