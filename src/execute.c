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

		debug_cmd(cmd, "curr cmd (start)");

		// DEBUG
		debug_read_fd("cmd->fdin", cmd->fdin);
		// END DEBUG

		if (cmd->pipe_after) {
			if (pipe(fds) == -1)
				exit_exec(pinput, "pipe"); // TODO leaks
			cmd->fdout = fds[1];
			(*pinput)->next->cmd->fdin = fds[0];
		}
		debug_fd("curr->fdin", cmd->fdin);
		debug_fd("curr->fdout", cmd->fdout);
		debug_fd("next->fdin", (*pinput)->next->cmd->fdin);

		pid = fork();
		if (pid < 0)
			exit_exec(pinput, "fork"); // TODO leaks
		if (pid == 0) {
			ft_printf("=== CHILD PROCESS ====================\n");
			ft_printf("--- dup outfile --------------------------\n");
			if (cmd->pipe_after == 1)
			{
				close(fds[0]);
				if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
					exit_exec(pinput, "dup2 pipe");
				close(cmd->fdout);
				debug_read_fd("(HERE) next->fdin", ((*pinput)->next->cmd->fdin));
			}	
			else if (cmd->outfile != NULL) {
				cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd->fdout == -1)
					exit_exec(pinput, "open outfile"); // TODO leaks
				if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
					exit_exec(pinput, "dup2 outfile"); // TODO leaks
				close(cmd->fdout);
			}
			ft_printf("--- dup infile --------------------------\n");
			if (cmd->infile != NULL) {
				cmd->fdin = open(cmd->infile, O_RDONLY);
				if (cmd->fdin == -1)
					exit_exec(pinput, "open infile"); // TODO leaks
				if (dup2(cmd->fdin, STDIN_FILENO) == -1)
					exit_exec(pinput, "dup2 infile"); // TODO leaks
				close(cmd->fdin);
			}

			ft_printf("--- closing remaining cmd->fdin / cmd->fdout ------------\n");
			if (cmd->fdin != -1 && cmd->fdin != STDIN_FILENO) {
				//debug_fd("cmd->fdin", cmd->fdin);
				//debug_fd("STDIN_FILENO", STDIN_FILENO);
				close(cmd->fdin);
				cmd->fdin = -1;
				//debug_fd("cmd->fdin", cmd->fdin);
				//debug_fd("STDIN_FILENO", STDIN_FILENO);
			}
			if (cmd->fdout != -1 && cmd->fdout != STDOUT_FILENO) {
				close(cmd->fdout);
				cmd->fdout = -1;
			}
			exec_path = get_exec_path(cmd->args[0], pinput); // TODO check error

			//ft_printf("[exec_path: %s]\n", exec_path);

			debug_cmd(cmd, "curr cmd");
			ft_printf("--- Executing command -------------------\n");

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
