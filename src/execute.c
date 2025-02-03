#include "minishell.h"

void	execute_input(t_node **pinput, char **envp)
{
	t_node	*pi = *pinput;
	pid_t	pid;
	int		fdin = STDIN_FILENO;
	int		fdout = STDOUT_FILENO;
	char	*exec_path;
	int		status;

	while (pi)
	{
		t_cmd	*cmd = pi->cmd;

		if (pi->next)
			pipe(cmd->fds);
		debug_cmd(cmd, cmd->args[0]); // TODO debug
		pid = fork();
		if (pid < 0)
			exit_exec(pinput, "fork");
		if (pid == 0)
		{
			// dup stdin
			if (pi->prev)
				fdin = pi->prev->cmd->fds[0];
			else if (cmd->infile)
				fdin = open(cmd->infile, O_RDONLY);
			if (fdin != STDIN_FILENO)
			{
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}
			// dup stdout
			if (pi->next) // if we created a pipe in this loop:
			{
				close(cmd->fds[0]); // we won't read in pipe in this loop
				fdout = cmd->fds[1];
			}
			else if (cmd->outfile)
				fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
			if (fdout != STDOUT_FILENO)
			{
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}
			// execute cmd
			exec_path = get_exec_path(cmd->args[0], pinput);
			execve(exec_path, cmd->args, envp);
			exit(127);
		}
		waitpid(pid, &status, 0);
		if (pi->next) // if we created a pipe in this loop:
			close(cmd->fds[1]); // we won't write in pipe in next loop
		if (pi->prev) // if we created a pipe in the previous loop:
			close(pi->prev->cmd->fds[0]); // we finished reading in previous pipe
		pi = pi->next;
	}
}
