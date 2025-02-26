#include "minishell.h"

/**
 * Update cmd->fdin and cmd->fdout if the current t_cmd contains an infile
 * or an outfile.
 * 
 * @param cmd Struct of the command to execute
 * @param minishell Struct containing global Minishell data (to be freed
 *  in case of failure)
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 * @note Exit on: pipe failure, open failure
 */
static int	setup_io(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_minishell(EXIT_FAILURE, minishell, "pipe");
	}
	if (cmd->prev)
		cmd->fdin = cmd->prev->pipe[0];
	else if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			return (put_error(cmd->infile), EXIT_FAILURE);
	}
	if (cmd->next)
		cmd->fdout = cmd->pipe[1];
	else if (cmd->outfile)
	{
		cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			return (put_error(cmd->outfile), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Closes unnecessary file descriptors for the current command in the
 * parent process.
 * 
 * This ensures that the reference count for each file descriptor is
 * decremented, allowing EOF to be triggered when the child process closes 
 * its end of the pipe.
 * 
 * Closes:
 * - cmd->fdin if an input file is specified
 * - cmd->fdout if an output file is specified
 * - The write end of the pipe if created for this command
 * - The read end of the pipe if created for the previous command
 * 
 * @param cmd Struct of the command to execute
 * @return void
 * @note Exit on: None
 */
static void	cleanup_io(t_cmd *cmd)
{
	if (cmd->infile)
		close_fd(cmd->fdin);
	if (cmd->outfile)
		close_fd(cmd->fdout);
	if (cmd->next)
		close_fd(cmd->pipe[1]);
	if (cmd->prev)
		close_fd(cmd->prev->pipe[0]);
}

/**
 * Wait for all processes to finish and handle exit codes. 
 *
 * @param minishell Struct containing global Minishell data (to be 
 *  freed in case of failure)
 * @return void
 * @note Exit on: a process exits with code > E_ERRMAX
 */
static void	wait_for_processes(t_minishell *minishell)
{
	t_cmd	*cmd;
	int		status;

	cmd = minishell->cmd_lst;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			if (waitpid(cmd->pid, &status, 0) > 0)
			{
				if (WIFEXITED(status))
					minishell->exit_code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					minishell->exit_code = 128 + WTERMSIG(status);
			}
		}
		cmd = cmd->next;
	}
}

/**
 * Execute one command (t_cmd).
 * 
 * If setup_io() fails, don't execute cmd and set ms->exit_code
 * on EXIT_FAILURE.
 * If is a builtin that does not affect state and with no pipes,
 * run it in parent process, else run builtin or executable in 
 * child process.
 * 
 * @param cmd The command to execute
 * @param ms Struct containing global Minishell data (to be 
 *  freed in case of failure)
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static void	execute_cmd(t_cmd *cmd, t_minishell *ms)
{
	t_builtin	*builtin;

	if (cmd->args && cmd->args[0] && cmd->args[0][0] != '\0')
	{
		if (setup_io(cmd, ms) == EXIT_FAILURE)
			ms->exit_code = EXIT_FAILURE;
		else
		{
			builtin = get_builtin(cmd->args[0]);
			if (builtin && builtin->affects_state && !cmd->next && !cmd->prev)
				run_builtin(FALSE, builtin, cmd->args, ms);
			else
				cmd->pid = run_in_child_process(builtin, cmd, ms);
			cleanup_io(cmd);
		}
	}
}

/**
 * Execute each t_cmd of the list one by one.
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
	cmd = ms->cmd_lst;
	while (cmd)
	{
		execute_cmd(cmd, ms);
		cmd = cmd->next;
	}
	wait_for_processes(ms);
}
