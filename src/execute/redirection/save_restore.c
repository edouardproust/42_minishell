#include "minishell.h"

/**
 * Saves the current stdin and stdout file descriptors.
 * 
 * This function is used before proceeding to fd redirections in the parent
 * process. This way, we'll be able to restore stdin and stdout once the
 * redirections have been made.
 * Stdin and fdout's fds are saved inside the cmd struct.
 *
 * @param cmd Command to execute.
 * @param ms Minishell data (freed on failure).
 * @note Exits on dup failure.
 */
void	save_stdin_stdout(t_cmd *cmd, t_minishell *ms)
{
	if (cmd->infile)
	{
		if (ft_dup(STDIN_FILENO, &cmd->saved_stdin) == EXIT_FAILURE)
			exit_minishell(EXIT_FAILURE, ms, "dup");
	}
	if (cmd->outfile)
	{
		if (ft_dup(STDOUT_FILENO, &cmd->saved_stdout) == EXIT_FAILURE)
		{
			ft_close(&cmd->saved_stdin);
			exit_minishell(EXIT_FAILURE, ms, "dup");
		}
	}
}

/**
 * Restores the original stdin and stdout file descriptors.
 * 
 * This function is used once the fd redirections have been made inside the
 * parent process, so we can move on normally for the next command.
 * It closed saved fds after restoration, and set them to -1.
 *
 * @param cmd Command to execute.
 * @param ms Minishell data (freed on failure).
 * @note Exits on dup2 failure.
 */
void	restore_stdin_stdout(t_cmd *cmd, t_minishell *ms)
{
	if (cmd->infile && cmd->saved_stdin != -1)
	{
		if (ft_dup2(cmd->saved_stdin, STDIN_FILENO) == EXIT_FAILURE)
			exit_minishell(EXIT_FAILURE, ms, "dup2");
	}
	if (cmd->outfile && cmd->saved_stdout != -1)
	{
		if (ft_dup2(cmd->saved_stdout, STDOUT_FILENO) == EXIT_FAILURE)
			exit_minishell(EXIT_FAILURE, ms, "dup2");
	}
}
