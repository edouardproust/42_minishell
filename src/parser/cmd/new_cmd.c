/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:46 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:53 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initializes process-related fields in the t_cmd structure.
 *
 * @param cmd The command structure to initialize.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on malloc failure.
 */
static int	init_cmd_process(t_cmd *cmd)
{
	cmd->pid = -1;
	cmd->pipe = malloc(sizeof(int) * 2);
	if (!cmd->pipe)
		return (EXIT_FAILURE);
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->saved_stdin = -1;
	cmd->saved_stdout = -1;
	return (EXIT_SUCCESS);
}

/**
 * Initializes redirection-related fields in the t_cmd structure.
 *
 * @param cmd The command structure to initialize.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on heredoc initialization
 * failure.
 */
static int	init_cmd_redirections(t_cmd *cmd)
{
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->infiles = NULL;
	cmd->outfiles = NULL;
	return (EXIT_SUCCESS);
}

/**
 * Creates a new command structure with default values.
 *
 * @param prev_cmd The previous command in the list, or NULL if this is the
 * first command.
 * @return A new t_cmd structure on success, NULL on malloc failure.
 */
t_cmd	*cmd_new(t_cmd *prev_cmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	if (init_cmd_process(cmd) != EXIT_SUCCESS)
		return (free_cmd_node(&cmd), NULL);
	if (init_cmd_redirections(cmd) != EXIT_SUCCESS)
		return (free_cmd_node(&cmd), NULL);
	cmd->prev = prev_cmd;
	if (cmd->prev)
		cmd->prev->next = cmd;
	cmd->next = NULL;
	return (cmd);
}
