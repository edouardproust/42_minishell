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

void	execute_cmd_lst(t_cmd **cmd_lst, char **envp)
{
	t_cmd		*cmd;
	t_builtin	*builtin;

	cmd = *cmd_lst;
	if (!cmd_lst || !*cmd_lst)
		exit_exec(NULL, "Incorrect parsed command");
	while (cmd)
	{
		if (DEBUG)
			debug_cmd(cmd, cmd->args[0]); // DEBUG
		setup_io(cmd, cmd_lst);
		builtin = get_builtin(cmd->args[0]);
		if (builtin && builtin->affects_state)
			run_builtin(builtin, cmd->args, cmd_lst);
		else
			run_executable(builtin, cmd, envp, cmd_lst);
		cleanup_io(cmd);
		cmd = cmd->next;
	}
}
