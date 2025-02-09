#include "minishell.h"

/*
 * Updates cmd->fdin and cmd->fdout if the current t_cmd contains an infile
 * or an outfile.
 * 
 * Exit on: pipe failure, open failure
 */
static void	setup_io(t_cmd *cmd, t_cmd **cmd_lst)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_exec(EXIT_FAILURE, cmd_lst, "pipe");
	}
	if (cmd->prev)
		cmd->fdin = cmd->prev->pipe[0];
	else if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			exit_exec(EXIT_FAILURE, cmd_lst, cmd->infile);
	}
	if (cmd->next)
		cmd->fdout = cmd->pipe[1];
	else if (cmd->outfile)
	{
		cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			exit_exec(EXIT_FAILURE, cmd_lst, cmd->outfile);
	}
}

/*
 * Closes the uncessary file descriptors for the current t_cmd:
 * - cmd->fdin if there is an infile
 * - cmd->outfile if there is an outfile
 * - pipe's write end if we created a pipe in this cmd
 * - pipe's read end if we created a pipe in the previous cmd
 * 
 * Exit on: none
 */
static void	cleanup_io(t_cmd *cmd)
{
	if (cmd->infile)
		close(cmd->fdin);
	if (cmd->outfile)
		close(cmd->fdout);
	if (cmd->next)
		close(cmd->pipe[1]);
	if (cmd->prev)
		close(cmd->prev->pipe[0]);
}

/*
 * Execute each t_cmd of the list one by one.
 *
 * Exit on: incorrect input, function call exit
 */
void	execute_cmd_lst(t_cmd **cmd_lst, char **envp)
{
	t_cmd		*cmd;
	t_builtin	*builtin;

	cmd = *cmd_lst;
	if (!cmd_lst || !*cmd_lst)
		exit_exec(EXIT_FAILURE, NULL, "Incorrect parsed command");
	while (cmd)
	{
		if (DEBUG)
			debug_cmd(cmd, cmd->args[0]); // DEBUG
		setup_io(cmd, cmd_lst);
		builtin = get_builtin(cmd->args[0]);
		if (builtin && builtin->affects_state)
			run_builtin(builtin, cmd->args, cmd_lst);
		else
			run_in_child_process(builtin, cmd, envp, cmd_lst);
		cleanup_io(cmd);
		cmd = cmd->next;
	}
}
