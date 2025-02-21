#include "minishell.h"

static void	setup_io(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			exit_minishell(EXIT_FAILURE, minishell, "pipe");
	}
	if (cmd->prev)
		cmd->fdin = cmd->prev->pipe[0];
	else if (cmd->infile)
	{
		cmd->fdin = open(cmd->infile, O_RDONLY);
		if (cmd->fdin == -1)
			exit_minishell(EXIT_FAILURE, minishell, cmd->infile);
	}
	if (cmd->next)
		cmd->fdout = cmd->pipe[1];
	else if (cmd->outfile)
	{
		cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fdout == -1)
			exit_minishell(EXIT_FAILURE, minishell, cmd->outfile);
	}
}

static void	cleanup_io(t_cmd *cmd)
{
	if (cmd->infile)
		close_fd(cmd->fdin);
	if (cmd->outfile)
		close_fd(cmd->fdout);
	if (cmd->next)
		close_fd(cmd->pipe[1]);
	if (cmd->prev)
		close_fd(cmd->prev->pipe[0]);
}

static void	duplicate_io(int newfd, int oldfd, t_minishell *minishell)
{
	if (dup2(newfd, oldfd) == -1)
		exit_minishell(EXIT_FAILURE, minishell, "dup2");
	close(newfd);
}

static void	execute_cmd(t_cmd *cmd, t_minishell *minishell)
{
	pid_t	pid;
	char	*exec_path;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_minishell(EXIT_FAILURE, minishell, "fork");
	if (pid == 0)
	{
		if (cmd->fdin != STDIN_FILENO)
			duplicate_io(cmd->fdin, STDIN_FILENO, minishell);
		if (cmd->fdout != STDOUT_FILENO)
			duplicate_io(cmd->fdout, STDOUT_FILENO, minishell);
		exec_path = get_exec_path(cmd->args[0], minishell);
		execve(exec_path, cmd->args, minishell->envp);
		exit_minishell(EXIT_FAILURE, minishell, exec_path);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) >= E_CMDNOTEXEC)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
}

void	execute_cmd_lst(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->cmd_lst;
	while (cmd)
	{
		if (ft_matrix_size(cmd->args) != 0)
		{
			setup_io(cmd, minishell);
			execute_cmd(cmd, minishell);
			cleanup_io(cmd);
		}
		cmd = cmd->next;
	}
}
