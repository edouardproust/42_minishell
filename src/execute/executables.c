#include "minishell.h"

static int	duplicate_fd(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (EXIT_SUCCESS);
	if (dup2(oldfd, newfd) == -1)
			return (EXIT_FAILURE);
		close(oldfd);
	return (EXIT_SUCCESS);
}

static void	redirect_io(t_cmd *cmd)
{
	int	res;

	res = EXIT_SUCCESS;
	if (cmd->fdin != STDIN_FILENO)
		res = duplicate_fd(cmd->fdin, STDIN_FILENO);
	if (cmd->fdout != STDOUT_FILENO)
		res = duplicate_fd(cmd->fdout, STDOUT_FILENO);
	if (res != EXIT_SUCCESS)
		exit(E_CMDNOTEXEC);
}

void	run_executable(t_builtin *builtin, t_cmd *cmd, char **envp,
	t_cmd **cmd_lst)
{
	pid_t	pid;
	char	*exec_path;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_exec(cmd_lst, "fork");
	if (pid == 0)
	{
		redirect_io(cmd);
		if (builtin)
			run_builtin(builtin, cmd->args, cmd_lst);
		exec_path = get_exec_path(cmd->args[0], cmd_lst);
		execve(exec_path, cmd->args, envp);
		exit(E_CMDNOTFOUND);
	}
	waitpid(pid, &status, 0);
	ft_fprintf(STDERR_FILENO, "(STATUS: %d)\n", WEXITSTATUS(status));
	if (WIFEXITED(status) && WEXITSTATUS(status) > E_CMDNOTEXEC)
		exit_exec(cmd_lst, NULL);
}
