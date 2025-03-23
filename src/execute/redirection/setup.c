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

static int	setup_redir_infiles(t_cmd *cmd)
{
	int		i;

	if (!cmd->infiles)
		return (EXIT_SUCCESS);
	i = 0;
	while (cmd->infiles[i])
	{
		set_infile_fdin(cmd, cmd->infiles[i]);
		if (cmd->fdin == -1)
			return (EXIT_FAILURE);
		if (cmd->infiles[i + 1] == NULL)
		{
			if (duplicate_last_infile(cmd, cmd->infiles[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		ft_close(&cmd->fdin);
		i++;
	}
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
	int	i;

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
	if (setup_redir_infiles(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (setup_redir_outfiles(cmd));
}
