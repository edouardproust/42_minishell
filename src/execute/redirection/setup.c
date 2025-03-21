/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	setup_redir_heredoc(t_cmd *cmd, t_infile *infile)
{
	cmd->fdin = infile->hdoc_fd;
	if (cmd->fdin = -1)
		return (put_error("heredoc: invalid fd"), EXIT_FAILURE);
	if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
	{
		ft_close(&cmd->fdin);
		infile->hdoc_fd = -1;
		return (put_error("heredoc: dup2"), EXIT_FAILURE);
	}
	ft_close(&cmd->fdin);
	infile->hdoc_fd = -1;
	return (EXIT_SUCCESS);
}

static int	setup_redir_infile(t_cmd *cmd, char *filepath)
{
	cmd->fdin = open(filepath, O_RDONLY);
	if (cmd->fdin == -1)
		return (put_error(filepath), EXIT_FAILURE);
	if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
	{
		ft_close(&cmd->fdin);
		return (put_error1("%s: dup2", filepath), EXIT_FAILURE);
	}
	ft_close(&cmd->fdin);
	return (EXIT_SUCCESS);
}

static int	setup_redir_outfile(t_cmd *cmd, t_outfile *outfile)
{
	int	flags;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	if (outfile->append)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fdout = open(outfile->filepath, flags, 0644);
	if (cmd->fdout == -1)
		return (put_error(outfile->filepath), EXIT_FAILURE);
	if (ft_dup2(cmd->fdout, STDOUT_FILENO) == EXIT_FAILURE)
	{
		ft_close(&cmd->fdout);
		return (put_error1("%s: dup2", outfile->filepath), EXIT_FAILURE);
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
	t_infile	*last_in;
	t_outfile	*last_out;
	int			ret;

	last_in = get_last_infile(cmd->infiles);
	if (last_in)
	{
		if (last_in->is_heredoc)
			ret = setup_redir_heredoc(cmd, last_in);
		else
			ret = setup_redir_infile(cmd, last_in->filepath);
		if (ret != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	last_out = get_last_outfile(cmd->outfiles);
	if (last_out)
	{
		ret = setup_redir_outfile(cmd, last_out);
		if (ret != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
