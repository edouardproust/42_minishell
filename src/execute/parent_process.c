#include "minishell.h"

static t_bool	handle_signaled_parent_process(t_minishell *ms,
	pid_t pid, int *status)
{
	if (pid == -1 && errno == EINTR)
	{
		kill_all_children(ms);
		ms->exit_code = E_SIGBASE + get_and_reset_signal();
		while (waitpid(-1, status, WNOHANG) > 0)
			;
		return (TRUE);
	}
	return (FALSE);
}

/**
 * Wait for all processes to finish and handle exit codes. 
 *
 * @param minishell Struct containing global Minishell data (to be 
 *  freed in case of failure)
 * @return void
 * @note Exit on: a process exits with code > E_ERRMAX
 */
static void	wait_for_processes(t_minishell *ms)
{
	t_cmd	*cmd;
	int		status;
	pid_t	pid;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			pid = waitpid(cmd->pid, &status, 0);
			if (handle_signaled_parent_process(ms, pid, &status))
			{
				ft_fprintf(STDERR_FILENO, "(signaled_parent)"); //DEBUG
				return ;
			}
			else if (WIFEXITED(status))
			{
				ft_fprintf(STDERR_FILENO, "(WIFEXITED)"); //DEBUG
				ms->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				ft_fprintf(STDERR_FILENO, "(WIFSIGNALED)"); //DEBUG
				put_signal_message(status);
				ms->exit_code = E_SIGBASE + WTERMSIG(status);
			}
		}
		cmd = cmd->next;
	}
}

/**
 * Execute one command (t_cmd).
 * 
 * Create a pipe if the cmd is followed by another. 
 * If a pipe has been created or the cmd's first does not correspond to a
 * builtin, the execution happens in a child process via the
 * `run_in_child_process` function.
 * Otherwise, the builtin is ran directly in the parent process. In this case,
 * stdin and stdout fds are saved before execution, and are restored after.
 * Finaly, close the pipe if one was created for this command.

 * @return void
 */
static void	execute_cmd(t_cmd *cmd, t_minishell *ms)
{
	t_builtin	*builtin;

	init_pipe_if(cmd, ms);
	builtin = get_builtin(cmd);
	if (cmd->prev || cmd->next || !builtin)
		cmd->pid = run_in_child_process(builtin, cmd, ms);
	else
	{
		save_stdin_stdout(cmd, ms);
		if (setup_redirections(cmd) == EXIT_SUCCESS)
			run_builtin(FALSE, builtin, cmd->args, ms);
		restore_stdin_stdout(cmd, ms);
	}
	close_pipe_if(cmd);
}

/**
 * Execute each t_cmd of the list one by one.
 *
 * Checks if a command has a heredoc, it is processed before execution.
 *
 * Loop over the commands list, calling `execute_cmd`. Then wait for each process
 * to finish.
 * 
 * @param ms Struct containing global Minishell data (to be 
 *  freed in case of failure)
 * @return void
 * @note Exit on: incorrect input, function call exit
 */
void	execute_cmd_lst(t_minishell *ms)
{
	t_cmd		*cmd;

	if (!ms || !ms->cmd_lst)
		exit_minishell(EXIT_FAILURE, NULL, "Incorrect parsed command");
	if (process_all_heredocs(ms) != EXIT_SUCCESS)
		return ;
	cmd = ms->cmd_lst;
	while (cmd)
	{
		execute_cmd(cmd, ms);
		cmd = cmd->next;
	}
	wait_for_processes(ms);
}
