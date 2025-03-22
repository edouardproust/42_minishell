/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:35:35 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:35:40 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a t_cmd has any input files (infiles) or output files (outfiles).
 *
 * @param cmd Pointer to the t_cmd struct.
 * @return TRUE if infiles or outfiles exist, FALSE otherwise.
 */
t_bool	cmd_has_redirections(t_cmd *cmd)
{
	t_bool	ret;

	ret = FALSE;
	if (cmd->infiles != NULL && cmd->infiles[0] != NULL)
		ret = TRUE;
	if (cmd->outfiles != NULL && cmd->outfiles[0] != NULL)
		ret = TRUE;
	return (ret);
}

/**
 * Check if the command is a forbidden one.
 *
 * Display an error if the command is forbidden.
 *
 * @param cmd The command to check
 * @return TRUE if the cmd is forbidden, or FALSE
 */
t_bool	is_forbidden_cmd(t_cmd *cmd)
{
	if (ft_matrix_size(cmd->args) == 0)
		return (FALSE);
	if (cmd->prev || cmd->next)
	{
		if (ft_strcmp("./minishell", cmd->args[0]) == 0)
			return (put_error("cannot call itself in a sub-process"), TRUE);
	}
	return (FALSE);
}
