/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a child process and run a builtin or an executable in it.
 *
 * @param builtin Struct containing data on the builtin to be executed.
 *  NULL if an executable must be executed instead.
 * @param cmd Struct of the command to be executed. NULL if a builtin
 *  must be executed instead.
 * @return Child process PID
 * @note Exit on: fork failure, child process exit code > E_ERRMAX
 */
pid_t	run_in_child_process(t_builtin *builtin, t_cmd *cmd,
	t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_minishell(EXIT_FAILURE, minishell, "fork");
	if (pid == 0)
	{
		setup_pipe_ends(cmd, minishell);
		if (setup_redirections(cmd) == EXIT_FAILURE)
			exit_minishell(EXIT_FAILURE, minishell, NULL);
		if (ft_matrix_size(cmd->args) == 0)
			exit_minishell(EXIT_SUCCESS, minishell, NULL);
		if (builtin)
			run_builtin(TRUE, builtin, cmd->args, minishell);
		run_executable(cmd, minishell);
	}
	return (pid);
}
