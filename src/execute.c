#include "minishell.h"

void	execute_input(t_node **pinput, char **envp)
{
	int		fds[2];
	char	*exec_path;
	pid_t	pid;
	int		status;

	while (*pinput)
	{
		t_cmd *cmd = (*pinput)->cmd;

		//ft_printf("(in: %d, out: %d)\n", fcntl(STDIN_FILENO, F_GETFL), fcntl(STDOUT_FILENO, F_GETFL));
		test_print_cmd(cmd); // TODO DEBUG remove
		if (cmd->pipe_after) {
			if (pipe(fds) == -1)
				exit_exec(pinput, "pipe"); // TODO leaks
			cmd->fdout = fds[1];
			(*pinput)->next->cmd->fdin = fds[0];
		}
		pid = fork();
		if (pid < 0)
			exit_exec(pinput, "fork"); // TODO leaks
		if (pid == 0) {
			if (cmd->pipe_after)
				close(fds[0]);	
			if (cmd->infile) {
				cmd->fdin = open(cmd->infile, O_RDONLY);
				if (cmd->fdin == -1)
					exit_exec(pinput, "open infile"); // TODO leaks
				if (dup2(cmd->fdin, STDIN_FILENO) == -1)
					exit_exec(pinput, "dup2 infile"); // TODO leaks
				close(cmd->fdin);
			}
			if (cmd->outfile) {
				cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd->fdout == -1)
					exit_exec(pinput, "open outfile"); // TODO leaks
				if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
					exit_exec(pinput, "dup2 outfile"); // TODO leaks
				close(cmd->fdout);
			}
			if (cmd->fdin != -1 && cmd->fdin != STDIN_FILENO) {
				close(cmd->fdin);
				cmd->fdin = -1;
			}
			if (cmd->fdout != -1 && cmd->fdout != STDOUT_FILENO) {
				close(cmd->fdout);
				cmd->fdout = -1;
			}
			exec_path = get_exec_path(cmd->args[0], pinput); // TODO check error
			ft_printf("[exec_path: %s]\n", exec_path); // TODO DEBUG	
			test_print_cmd(cmd); // TODO DEBUG remove
			execve(exec_path, cmd->args, envp);
			exit(127);
		}
		if (cmd->pipe_after)
			close(fds[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_exec(pinput, "execve"); // TODO leaks
		(*pinput) = (*pinput)->next;
	}
}
