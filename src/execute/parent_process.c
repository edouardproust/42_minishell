#include "minishell.h"
# include "debug.h" // TODO: remove

/*
 * Update cmd->fdin and cmd->fdout if the current t_cmd contains an infile
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

/**
 * Closes unnecessary file descriptors for the current command in the parent process.
 * 
 * This ensures that the reference count for each file descriptor is decremented,
 * allowing EOF to be triggered when the child process closes its end of the pipe.
 * 
 * Closes:
 * - cmd->fdin if an input file is specified
 * - cmd->fdout if an output file is specified
 * - The write end of the pipe if created for this command
 * - The read end of the pipe if created for the previous command
 * 
 * Exit on: None
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
 * Wait for all processes to finish and handle exit codes. 
 *
 * Exit on: a process exits with code > 125
 */
static void	wait_for_processes(t_cmd **cmd_lst)
{
	t_cmd	*cmd;
	int		status;
	
	cmd = *cmd_lst;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (DEBUG) // DEBUG
				debug_process(cmd->pid, status);
			if (WIFEXITED(status) && WEXITSTATUS(status) >= E_CMDNOTEXEC)
				exit_exec(WEXITSTATUS(status), cmd_lst, NULL);
		}
		cmd = cmd->next;
	}
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
		setup_io(cmd, cmd_lst);
		builtin = get_builtin(cmd->args[0]);
		if (builtin && builtin->affects_state)
			run_builtin(0, builtin, cmd->args, cmd_lst);
		else
			cmd->pid = run_in_child_process(builtin, cmd, envp, cmd_lst);
		if (DEBUG) // DEBUG
			debug_cmd(cmd, cmd->args[0]);
		cleanup_io(cmd);
		cmd = cmd->next;
	}
	wait_for_processes(cmd_lst);
}
