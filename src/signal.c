#include "minishell.h"

int	g_signal;

static void	signal_handler(int signal)
{
	g_signal = signal;
	if (g_signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		put_error("sigaction");
		exit(EXIT_FAILURE);
	}
}