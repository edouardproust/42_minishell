#include "minishell.h"

static volatile sig_atomic_t	g_signal = 0;

int	get_and_reset_signal(void)
{
	int	sig;
	
	sig = g_signal;
	g_signal = 0;
	return (sig);
}

void	exec_sigint_handler(int signal)
{
	g_signal = signal;
}

void	rl_sigint_handler(int signal)
{
	g_signal = signal;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// TODO deal with SIG_ERR when signal() fails
void	set_sigint_sigquit(__sighandler_t sigint_handler,
	__sighandler_t sigquit_handler)
{
	ft_signal(SIGINT, sigint_handler);
	ft_signal(SIGQUIT, sigquit_handler);
}
