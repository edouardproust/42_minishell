#include "minishell.h"

/*
 * Duplicates a file descriptor.
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
 * Redirects input and output for the current t_cmd if necessary.
 *
 * Exit on: duplication failure
 */
static void	redirect_io(t_cmd *cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->fdin != STDIN_FILENO)
		exit_code = duplicate_fd(cmd->fdin, STDIN_FILENO);
	if (cmd->fdout != STDOUT_FILENO)
		exit_code = duplicate_fd(cmd->fdout, STDOUT_FILENO);
	if (exit_code != EXIT_SUCCESS)
		exit_exec(exit_code, NULL, "dup2"); // TODO: test exit
}

/*
 * Creates a child process and run a builtin or an executable in it.
 *
 * Exit on: fork failure, child process exit code > 125
 */
void	run_in_child_process(t_builtin *builtin, t_cmd *cmd, char **envp,
	t_cmd **cmd_lst)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_exec(EXIT_FAILURE, cmd_lst, "fork");
	if (pid == 0)
	{
		redirect_io(cmd);
		if (builtin)
			run_builtin(builtin, cmd->args, cmd_lst);
		run_executable(cmd, envp, cmd_lst);
	}
	waitpid(pid, &status, 0);
	ft_fprintf(STDERR_FILENO, "[%d]\n", WEXITSTATUS(status)); // TODO: debug to be removed
	if (WIFEXITED(status) && WEXITSTATUS(status) >= E_CMDNOTEXEC)
		exit_exec(WEXITSTATUS(status), cmd_lst, NULL); // TODO: update exit code dynamically
}