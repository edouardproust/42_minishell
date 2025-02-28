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
static void	setup_pipe(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->prev)
		cmd->fdin = cmd->prev->pipe[0];
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_minishell(EXIT_FAILURE, minishell, "pipe");
		cmd->fdout = cmd->pipe[1];
	}
}

/**
 * Duplicate a file descriptor and close it once duplicated.
 *
 * @param oldfd File descriptor to duplicate
 * @param newfd Destination file descriptor
 * @return: EXIT_FAILURE if dup2 fails. EXIT_SUCCESS otherwise.
 */
int	duplicate_fd(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (EXIT_SUCCESS);
	if (dup2(oldfd, newfd) == -1)
		return (EXIT_FAILURE);
	close(oldfd);
	return (EXIT_SUCCESS);
}

/**
 * Redirect input and output for the current command if necessary.
 */
int	handle_redirections(t_cmd *cmd)
{
	if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			return (put_error(cmd->infile), EXIT_FAILURE);
		else if (duplicate_fd(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
			return (put_error("dup2"), EXIT_FAILURE);
	}
	if (cmd->outfile)
	{
		if (cmd->outfile_append == TRUE)
			cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			return (put_error(cmd->outfile), EXIT_FAILURE);
		else if (duplicate_fd(cmd->fdout, STDOUT_FILENO) == EXIT_FAILURE)
			return (put_error("dup2"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	handle_redirections_in_parent(t_cmd *cmd, t_minishell *ms)
{
	if (cmd->infile)
	{
		cmd->saved_stdin = dup(STDIN_FILENO);
		if (cmd->saved_stdin == -1)
			exit_minishell(EXIT_FAILURE, ms, "dup");
	}
	if (cmd->outfile)
	{
		cmd->saved_stdout = dup(STDOUT_FILENO);
		if (cmd->saved_stdout == -1)
		{
			if (cmd->saved_stdin != -1)
				close(cmd->saved_stdin);
			exit_minishell(EXIT_FAILURE, ms, "dup");
		}
	}
	return (handle_redirections(cmd));
}

static void	restore_redirections(t_cmd *cmd, t_minishell *ms)
{
	if (cmd->infile && cmd->saved_stdin != -1)
	{
		if (dup2(cmd->saved_stdin, STDIN_FILENO) == -1)
			exit_minishell(EXIT_FAILURE, ms, "dup2");
		close(cmd->saved_stdin);
	}
	if (cmd->outfile && cmd->saved_stdout != -1)
	{
		if (dup2(cmd->saved_stdout, STDOUT_FILENO) == -1)
			exit_minishell(EXIT_FAILURE, ms, "dup2");
		close(cmd->saved_stdout);
	}
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
 * - The write end of the pipe if created for this command
 * - The read end of the pipe if created for the previous command
 * 
 * @param cmd Struct of the command to execute
 * @return void
 * @note Exit on: None
 */
static void	cleanup_io(t_cmd *cmd)
{
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
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				minishell->exit_code = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
}

/**
 * Execute one command (t_cmd).
 * //TODO comment
 */
static void execute_cmd(t_cmd *cmd, t_minishell *ms)
{
    t_builtin *builtin;

    setup_pipe(cmd, ms);
    builtin = get_builtin(cmd);
    if (cmd->prev || cmd->next || !builtin)
        cmd->pid = run_in_child_process(builtin, cmd, ms);
	else
	{
		if (handle_redirections_in_parent(cmd, ms) == EXIT_SUCCESS)
			run_builtin(FALSE, builtin, cmd->args, ms);
		restore_redirections(cmd, ms);
	}
    cleanup_io(cmd);
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
