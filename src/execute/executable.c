/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Finds the executable path and runs it.
 *
 * @param cmd Struct of the command to be executed
 * @param minishell Struct containing global Minishell data, including
 * the environment array (`envp`)
 * @return void
 * @note Exit on: invalid path, execution failure
 */
void	run_executable(t_cmd *cmd, t_minishell *minishell)
{
	char	*exec_path;

	exec_path = get_exec_path(cmd->args[0], minishell);
	ft_signal(SIGQUIT, SIG_DFL);
	ft_signal(SIGINT, SIG_DFL);
	execve(exec_path, cmd->args, minishell->envp);
	exit(E_CMDNOTEXEC);
}
