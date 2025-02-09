#include "minishell.h"

/*
 * Finds the executable path and runs it.
 *
 * Exit on: invalid path, execution failure
 */
void	run_executable(t_cmd *cmd, char **envp, t_cmd **cmd_lst)
{
	char	*exec_path;

	exec_path = get_exec_path(cmd->args[0], cmd_lst);
	execve(exec_path, cmd->args, envp);
	exit(E_CMDNOTFOUND);
}