#include "minishell.h"

/**
 * Sets up input and output redirections for the current command.
 * 
 * Opens files and duplicates file descriptors as needed.
 *
 * @param cmd Command to execute.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	setup_redirections(t_cmd *cmd)
{
	if (cmd->heredoc_fd != -1)
	{
		cmd->fdin = cmd->heredoc_fd;
		cmd->heredoc_fd = -1;
		if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
			return (put_error("heredoc: dup2"), EXIT_FAILURE);
	}
	if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			return (put_error(cmd->infile), EXIT_FAILURE);
		if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
			return (put_error("%s: dup2", cmd->infile), EXIT_FAILURE);
	}
	if (cmd->outfile)
	{
		ft_close(&cmd->fdout);
		if (cmd->append)
			cmd->fdout = open(cmd->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			return (put_error(cmd->outfile), EXIT_FAILURE);
		if (ft_dup2(cmd->fdout, STDOUT_FILENO) == EXIT_FAILURE)
			return (put_error("%s: dup2", cmd->outfile), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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
		if (dup2(cmd->saved_stdin, STDIN_FILENO) == -1)
			exit_minishell(EXIT_FAILURE, ms, "dup2");
		ft_close(&cmd->saved_stdin);
	}
	if (cmd->outfile && cmd->saved_stdout != -1)
	{
		if (dup2(cmd->saved_stdout, STDOUT_FILENO) == -1)
			exit_minishell(EXIT_FAILURE, ms, "dup2");
		ft_close(&cmd->saved_stdout);
	}
}
