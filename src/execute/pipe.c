#include "minishell.h"

/**
 *  * Initializes pipe file descriptors for the current command if needed.
 *
 * Sets `cmd->fdin` to the read end of the previous command's pipe if it exists.
 * Creates a new pipe and sets `cmd->fdout` to its write end if there's a next
 * command.
 *
 * @param cmd Struct of the command to execute.
 * @param ms Struct containing global Minishell data (to be freed in case of
 * failure).
 * @return void
 * @note Exits on: pipe failure.
 */
void	init_pipe_if(t_cmd *cmd, t_minishell *ms)
{
	if (cmd->prev)
		cmd->fdin = cmd->prev->pipe[0];
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_minishell(EXIT_FAILURE, ms, "pipe");
		cmd->fdout = cmd->pipe[1];
	}
}

/**
 * Sets up input and output file descriptors for the current command.
 *
 * Duplicates `cmd->fdin` to `STDIN_FILENO` and `cmd->fdout` to `STDOUT_FILENO`
 * if needed.
 *
 * @param cmd Struct of the command to execute.
 * @param minishell Struct containing global Minishell data (to be freed in case
 *                 of failure).
 * @return void
 * @note Exits on: `dup2` failure.
 */
void	setup_pipe_ends(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->fdin != -1 && cmd->fdin != STDIN_FILENO)
	{
		if (ft_dup2(cmd->fdin, STDIN_FILENO))
			exit_minishell(EXIT_FAILURE, minishell, "pipe (in): dup2");
	}
	if (cmd->fdout != -1 && cmd->fdout != STDOUT_FILENO)
	{
		if (ft_dup2(cmd->fdout, STDOUT_FILENO))
			exit_minishell(EXIT_FAILURE, minishell, "pipe (out): dup2");
	}
}

/**
 * Closes unnecessary file descriptors in the parent process.
 *
 * Ensures proper reference counting and EOF handling by closing:
 * - The write end of the pipe if created for this command.
 * - The read end of the pipe if created for the previous command.
 *
 * @param cmd Command to execute.
 * @note No exit on failure.
 */
void	close_pipe_if(t_cmd *cmd)
{
	if (cmd->next)
		ft_close(&cmd->pipe[1]);
	if (cmd->prev)
		ft_close(&cmd->prev->pipe[0]);
}
