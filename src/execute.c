#include "minishell.h"

static void	setup_io(t_cmd *cmd, t_cmd **cmd_lst)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_exec(cmd_lst, "pipe");
	}
	if (cmd->prev)
		cmd->fdin = cmd->prev->pipe[0];
	else if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			exit_exec(cmd_lst, cmd->infile);
	}
	if (cmd->next) // if we created a pipe in this loop
		cmd->fdout = cmd->pipe[1];
	else if (cmd->outfile)
	{
		cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			exit_exec(cmd_lst, cmd->outfile);
	}
}

static void	cleanup_io(t_cmd *cmd)
{
	if (cmd->infile)
		close(cmd->fdin);
	if (cmd->outfile)
		close(cmd->fdout);
	if (cmd->next) // if we created a pipe in this loop
		close(cmd->pipe[1]); // we won't write in pipe in next loop
	if (cmd->prev) // if we created a pipe in the previous loop
		close(cmd->prev->pipe[0]); // we finished reading in previous pipe
}

static void	duplicate_io(int newfd, int oldfd, t_cmd **cmd_lst)
{
	if (dup2(newfd, oldfd) == -1)
		exit_exec(cmd_lst, "dup2");
	close(newfd);
}

static void	execute_cmd(t_cmd *cmd, char **envp, t_cmd **cmd_lst)
{
	pid_t	pid;
	char	*exec_path;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_exec(cmd_lst, "fork");
	if (pid == 0)
	{
		if (cmd->fdin != STDIN_FILENO)
			duplicate_io(cmd->fdin, STDIN_FILENO, cmd_lst);
		if (cmd->fdout != STDOUT_FILENO)
			duplicate_io(cmd->fdout, STDOUT_FILENO, cmd_lst);
		exec_path = get_exec_path(cmd->args[0], cmd_lst);
		execve(exec_path, cmd->args, envp);
		exit_exec(cmd_lst, exec_path);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		exit_exec(cmd_lst, NULL);
}

void	execute_cmd_lst(t_minishell **minishell)
{
	t_cmd	*cmd;

	cmd = (*minishell)->cmd_lst;
	while (cmd)
	{
		setup_io(cmd, &(*minishell)->cmd_lst);
		execute_cmd(cmd, (*minishell)->envp, &(*minishell)->cmd_lst);
		cleanup_io(cmd);
		cmd = cmd->next;
	}
}
