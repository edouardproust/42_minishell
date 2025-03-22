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
	if (cmd->fdin == -1)
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

/**
 * Create all the outfiles for the current command. Assign the last
 * outfile's fd to stdout.
 *
 * @param outfiles Array of outfiles
 * @return EXIT_SUCCESS, or EXIT_FAILURE if an intermediary outfile could not
 * be created or the dup of the last outfile on stdout failed. The function
 * prints error messages.
 */
static int	setup_redir_outfiles(t_cmd *cmd)
{
	int			i;

	if (!cmd->outfiles)
		return (EXIT_SUCCESS);
	i = 0;
	while (cmd->outfiles[i])
	{
		cmd->fdout = open_outfile(cmd->outfiles[i]);
		if (cmd->fdout == -1)
			return (put_error(cmd->outfiles[i]->filepath), EXIT_FAILURE);
		if (cmd->outfiles[i + 1] == NULL)
		{
			if (ft_dup2(cmd->fdout, STDOUT_FILENO) == EXIT_FAILURE)
			{
				ft_close(&cmd->fdout);
				return (put_error1("%s: dup2", cmd->outfiles[i]->filepath),
					EXIT_FAILURE);
			}
		}
		ft_close(&cmd->fdout);
		i++;
	}
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
	ret = setup_redir_outfiles(cmd);
	if (ret != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
