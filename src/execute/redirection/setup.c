#include "minishell.h"

static	int	setup_redir_heredoc(t_cmd *cmd)
{
	cmd->fdin = cmd->heredoc->fd;
	cmd->heredoc->fd = -1;
	if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
	{
		ft_close(&cmd->fdin);
		return (put_error("heredoc: dup2"), EXIT_FAILURE);
	}
	ft_close(&cmd->fdin);
	return (EXIT_SUCCESS);
}

static int	setup_redir_infile(t_cmd *cmd)
{
	cmd->fdin = open(cmd->infile, O_RDONLY);
	if (cmd->fdin == -1)
		return (put_error(cmd->infile), EXIT_FAILURE);
	if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
	{
		ft_close(&cmd->fdin);
		return (put_error1("%s: dup2", cmd->infile), EXIT_FAILURE);
	}
	ft_close(&cmd->fdin);
	return (EXIT_SUCCESS);
}

static int	setup_redir_outfile(t_cmd *cmd)
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
	{
		ft_close(&cmd->fdout);
		return (put_error1("%s: dup2", cmd->outfile), EXIT_FAILURE);
	}
	ft_close(&cmd->fdout);
	return (EXIT_SUCCESS);
}

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
	if (cmd->heredoc->fd != -1)
	{
		if (setup_redir_heredoc(cmd) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (cmd->infile)
	{
		if (setup_redir_infile(cmd) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (cmd->outfile)
	{
		if (setup_redir_outfile(cmd) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
