#include "minishell.h"

static volatile sig_atomic_t	g_signal = 0;

int	get_and_reset_signal(void)
{
	sig_atomic_t	sig;
	
	sig = g_signal;
	g_signal = 0;
	return (sig);
}

void	rl_sigint_handler(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_sigint_handler(int signal)
{
	g_signal = signal;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	close(STDIN_FILENO);
}

void	exec_sigint_handler(int signal)
{
	g_signal = signal;
}
