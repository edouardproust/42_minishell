/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
