#include "minishell.h"

static void	setup_io(t_node *pi, t_cmd *cmd, t_node **pinput)
{
	if (pi->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_exec(pinput, "pipe");
	}
	if (pi->prev)
		cmd->fdin = pi->prev->cmd->pipe[0];
	else if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			exit_exec(pinput, cmd->infile);
	}
	if (pi->next) // if we created a pipe in this loop
		cmd->fdout = cmd->pipe[1];
	else if (cmd->outfile)
	{
		cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			exit_exec(pinput, cmd->outfile);
	}
}

static void	duplicate_io(int newfd, int oldfd, t_node **pinput)
{
	if (dup2(newfd, oldfd) == -1)
		exit_exec(pinput, "dup2");
	close(newfd);
}

static void	execute_command(t_cmd *cmd, char **envp, t_node **pinput)
{
	pid_t	pid;
	char	*exec_path;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_exec(pinput, "fork");
	if (pid == 0)
	{
		if (cmd->fdin != STDIN_FILENO)
			duplicate_io(cmd->fdin, STDIN_FILENO, pinput);
		if (cmd->fdout != STDOUT_FILENO)
			duplicate_io(cmd->fdout, STDOUT_FILENO, pinput);
		exec_path = get_exec_path(cmd->args[0], pinput);
		execve(exec_path, cmd->args, envp);
		exit_exec(pinput, exec_path);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		exit_exec(pinput, NULL);
}

static void	cleanup_io(t_node *pi, t_cmd *cmd)
{
	if (cmd->infile)
		close(cmd->fdin);
	if (cmd->outfile)
		close(cmd->fdout);
	if (pi->next) // if we created a pipe in this loop
		close(cmd->pipe[1]); // we won't write in pipe in next loop
	if (pi->prev) // if we created a pipe in the previous loop
		close(pi->prev->cmd->pipe[0]); // we finished reading in previous pipe
}

void	execute_input(t_node **pinput, char **envp)
{
	t_node	*pi;
	t_cmd	*cmd;

	pi = *pinput;
	while (pi)
	{
		cmd = pi->cmd;
		setup_io(pi, cmd, pinput);
		debug_cmd(cmd, cmd->args[0]); // DEBUG
		execute_command(cmd, envp, pinput);
		cleanup_io(pi, cmd);
		pi = pi->next;
	}
}
