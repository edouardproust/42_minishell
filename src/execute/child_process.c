#include "minishell.h"

/**
 * Duplicate a file descriptor and close it once duplicated.
 *
 * @param oldfd File descriptor to duplicate
 * @param newfd Destination file descriptor
 * @return: EXIT_FAILURE if dup2 fails. EXIT_SUCCESS otherwise.
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

/**
 * Redirect input and output for the current command if necessary.
 *
 * @note Exit on: duplication failure
 * @return void
 * @note Exit on: a call to duplicate_fd fails
 */
static void	redirect_io(t_cmd *cmd, t_minishell *minishell)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->fdin != STDIN_FILENO)
		exit_code = duplicate_fd(cmd->fdin, STDIN_FILENO);
	if (cmd->fdout != STDOUT_FILENO)
		exit_code = duplicate_fd(cmd->fdout, STDOUT_FILENO);
	if (exit_code != EXIT_SUCCESS)
		exit_minishell(exit_code, minishell, "dup2");
}

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
		redirect_io(cmd, minishell);
		if (builtin)
			run_builtin(TRUE, builtin, cmd->args, minishell);
		run_executable(cmd, minishell);
	}
	return (pid);
}
