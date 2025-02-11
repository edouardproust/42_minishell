#include "minishell.h"

/*
 * Duplicate a file descriptor and close it once duplicated.
 *
 * Return: exit code (success or failure)
 */
static int	duplicate_fd(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (EXIT_SUCCESS);
	if (dup2(oldfd, newfd) == -1)
			return (EXIT_FAILURE);
		close(oldfd);
	return (EXIT_SUCCESS);
}

/*
 * Redirect input and output for the current command if necessary.
 *
 * Exit on: duplication failure
 */
static void	redirect_io(t_cmd *cmd, t_cmd **cmd_lst)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->fdin != STDIN_FILENO)
		exit_code = duplicate_fd(cmd->fdin, STDIN_FILENO);
	if (cmd->fdout != STDOUT_FILENO)
		exit_code = duplicate_fd(cmd->fdout, STDOUT_FILENO);
	if (exit_code != EXIT_SUCCESS)
		exit_exec(exit_code, cmd_lst, "dup2");
}

/*
 * Create a child process and run a builtin or an executable in it.:w
 *
 * Exit on: fork failure, child process exit code > 125
 */
pid_t	run_in_child_process(t_builtin *builtin, t_cmd *cmd, char **envp,
	t_cmd **cmd_lst)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_exec(EXIT_FAILURE, cmd_lst, "fork");
	if (pid == 0)
	{
		redirect_io(cmd, cmd_lst);
		if (builtin)
			run_builtin(1, builtin, cmd->args, cmd_lst);
		run_executable(cmd, envp, cmd_lst);
	}
	return (pid);
}
