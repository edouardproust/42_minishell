#include "minishell.h"

void	update_exit_code_if_signal(t_minishell *ms)
{
	int	sig;
	
	sig = get_and_reset_signal();
	if (sig)
		ms->exit_code = E_SIGBASE + sig;
}

void	put_signal_message(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf("Quit");
			if (WCOREDUMP(status))
				ft_printf(" (core dumped)");
		}
		ft_printf("\n");
	}
}

/**
 * Kill all children processes.
 * 
 * To be used in the parent process when a SIGINT signal
 * has been catched.
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

t_bool	ft_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa = {
		.sa_handler = handler,
		.sa_flags = SA_RESTART
	};

	sigemptyset(&sa.sa_mask);
	return (sigaction(signum, &sa, NULL) == 0);
}