#include "minishell.h"
#include "debug.h" //DEBUG

static volatile sig_atomic_t g_signal = 0;

/**
 * Checks if the global signal matches the given value.
 *
 * @param check The value to compare with the global signal.
 * @return Returns TRUE if the global signal equals `check`,
 * 	otherwise FALSE.
 */
t_bool	is_signal(int check)
{
	if (g_signal == check)
		return (TRUE);
	return (FALSE);
}

/**
 * Kill all children processes.
 * 
 * To be used in the parent process when a SIGINT signal
 * has been catched.
 */
void kill_all_children(t_minishell *ms) {
    t_cmd *cmd = ms->cmd_lst;
    while (cmd) {
        if (cmd->pid > 0 && kill(cmd->pid, 0) == 0)
		{
			kill(cmd->pid, SIGTERM);
            cmd->pid = -1;
        }
        cmd = cmd->next;
    }
}

static void	handle_sigint(int signal)
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

void init_signal_handlers(void)
{
    struct sigaction	sa_int;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
}