#include "minishell.h"

/**
 * Display the "Quit (core cump)" on SIGQUIT to mimic bash bahaviour
 * regarding background and foreground processes.
 * 
 * - Prints the message "Quit\n" only if the signaled process is the last
 * cmd in the cmd_lst.
 * - Adds "(core dump)" only if core dumps are activated on the machine
 */
void	put_sigquit_message(int status, t_cmd *cmd)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT && !cmd->next)
		{
			printf("Quit");
			if (WCOREDUMP(status))
				printf(" (core dumped)");
			printf("\n");
		}
	}
}

/**
 * Kill all children processes.
 * 
 * To be used in the parent process when a SIGINT signal
 * has been catched.
 * 
 * @param ms Struct holding global data about the program, including list
 * of commands (t_cmd)
 */
void	kill_all_children(t_minishell *ms)
{
	t_cmd	*cmd;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		if (cmd->pid > 0 && kill(cmd->pid, 0) == 0)
		{
			kill(cmd->pid, SIGTERM);
			cmd->pid = -1;
		}
		cmd = cmd->next;
	}
}

/**
 * Sets a signal handler for a specified signal.
 *
 * @param signum The signal number to set the handler for.
 * @param handler The function to be called when the signal is received.
 * @return TRUE if the signal handler was successfully set, FALSE otherwise.
 */
t_bool	ft_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	return (sigaction(signum, &sa, NULL) == 0);
}
