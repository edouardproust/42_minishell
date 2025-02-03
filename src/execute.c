#include "minishell.h"

static void	setup_io(t_node *pi, t_cmd *cmd, int *fdin, int *fdout, t_node **pinput)
{
	if (pi->next)
	{
		if (pipe(cmd->fds) == -1)
			exit_exec(pinput, "pipe");
	}
	if (pi->prev)
		*fdin = pi->prev->cmd->fds[0];
	else if (cmd->infile)
	{
		*fdin = open(cmd->infile, O_RDONLY);
		if (*fdin == -1)
			exit_exec(pinput, cmd->infile);
	}		
	if (pi->next) // if we created a pipe in this loop
		*fdout = cmd->fds[1];
	else if (cmd->outfile)
	{
		*fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fdout == -1)
			exit_exec(pinput, cmd->outfile);
	}
}

static void	duplicate_io(int newfd, int oldfd, t_node **pinput)
{
	if (dup2(newfd, oldfd) == -1)
		exit_exec(pinput, "dup2");
	close(newfd);
}

static void	execute_command(t_cmd *cmd, int fdin, int fdout, char **envp, t_node **pinput)
{
	pid_t	pid;
	char	*exec_path;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_exec(pinput, "fork");
	if (pid == 0)
	{
		if (fdin != STDIN_FILENO)
			duplicate_io(fdin, STDIN_FILENO, pinput);
		if (fdout != STDOUT_FILENO)
			duplicate_io(fdout, STDOUT_FILENO, pinput);
		exec_path = get_exec_path(cmd->args[0], pinput);
		execve(exec_path, cmd->args, envp);
		exit_exec(pinput, "%s", exec_path);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		exit_exec(pinput, NULL);
}

static void	cleanup_io(t_node *pi, t_cmd *cmd, int fdin, int fdout)
{
	if (cmd->infile)
		close(fdin);
	if (cmd->outfile)
		close(fdout);
	if (pi->next) // if we created a pipe in this loop
		close(cmd->fds[1]); // we won't write in pipe in next loop
	if (pi->prev) // if we created a pipe in the previous loop
		close(pi->prev->cmd->fds[0]); // we finished reading in previous pipe
}

void	execute_input(t_node **pinput, char **envp)
{
	int		fdin;
	int		fdout;
	t_node	*pi;
	t_cmd	*cmd;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	pi = *pinput;
	while (pi)
	{
		cmd = pi->cmd;
		setup_io(pi, cmd, &fdin, &fdout, pinput);
		//debug_cmd(cmd, cmd->args[0]); // DEBUG
		//debug_fd("child: fdin", fdin); debug_fd("child: fdout", fdout); // DEBUG
		execute_command(cmd, fdin, fdout, envp, pinput);
		cleanup_io(pi, cmd, fdin, fdout);
		pi = pi->next;
	}
}
