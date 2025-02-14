#include "minishell.h"

/*
 * Finds the executable path and runs it.
 *
 * Exit on: invalid path, execution failure
 */
void	run_executable(t_cmd *cmd, t_minishell **minishell)
{
	char	*exec_path;

	exec_path = get_exec_path(cmd->args[0], minishell);
	execve(exec_path, cmd->args, (*minishell)->envp);
	exit(E_CMDNOTFOUND);
}