#include "minishell.h"

/**
 * Reads heredoc input until delimiter, writing to pipe.
 * 
 * Reads the heredoc and writes each line to the write_fd descriptor.
 * The reading stops as soon as the delimiter (cmd->heredoc_del) is encountered.
 * 
 * @param cmd Command structure containing delimiter
 * @param write_fd Pipe write end file descriptor
 * @return EXIT_SUCCESS on delimiter match, EXIT_FAILURE on error/EOF
 */
static int	read_heredoc(t_cmd *cmd, int write_fd)
{
	char	*line;
	int		sig;
	int		exit_code;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (get_and_reset_signal() == SIGINT)
				return (ft_free(1, &line), E_SIGBASE + SIGINT);
			return (ft_free(1, &line), E_SIGBASE + SIGINT);
			put_error("warning: here-document at line %d delimited by "
				"end of file (wanted `%s')", cmd->heredoc->start,
				cmd->heredoc->delimiter);
			return (0);
		}
		if (ft_strcmp(line, cmd->heredoc->delimiter) == 0)
			return (ft_free(1, &line), EXIT_SUCCESS);
		if (ft_fprintf(write_fd, "%s\n", line) == -1)
			return (ft_free(1, &line), EXIT_FAILURE);
		ft_free(1, &line);
	}
	return (EXIT_SUCCESS);
}

/**
 * Handles child process for heredoc input collection.
 * 
 * @param pipefd Pipe file descriptors array
 * @param cmd Command structure containing heredoc details
 */
static void	handle_child_process(int *pipefd, t_cmd *cmd, t_minishell *ms)
{
	int	exit_code;

	ft_close(&pipefd[0]);
	ft_signal(SIGINT, heredoc_sigint_handler);
	exit_code = read_heredoc(cmd, pipefd[1]);
	flush_fds();
	free_minishell(&ms);
	exit(exit_code);
}

/**
 * Handles parent process after fork, manages pipe and waiting.
 * 
 * @param pid Child process ID
 * @param pipefd Pipe file descriptors array
 * @param cmd Command structure to store heredoc fd
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on child error
 */
static int	handle_parent_process(int pid, int *pipefd, t_cmd *cmd)
{
	int	status;

	ft_close(&pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		ft_close(&pipefd[0]);
		return (EXIT_FAILURE);
	}
	else if (WIFSIGNALED(status))
	{
		ft_close(&pipefd[0]);
		cmd->heredoc->fd = -1;
		return (E_SIGBASE + WTERMSIG(status));
	}
	cmd->heredoc->fd = pipefd[0];
	return (EXIT_SUCCESS);
}

/**
 * Manages heredoc processing using pipe communication.
 * 
 * @param cmd Command structure with heredoc details
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on pipe/fork error
 */
static int	process_heredoc(t_cmd *cmd, t_minishell *ms)
{
	int		pipefd[2];
	pid_t	pid;

	if (!cmd->heredoc->delimiter)
		return (EXIT_SUCCESS);
	if (pipe(pipefd) == -1)
		return (put_error("pipe"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0) 
	{
		ft_close(&pipefd[0]);
		ft_close(&pipefd[1]);
		return (put_error("fork"), EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(pipefd, cmd, ms);
	return (handle_parent_process(pid, pipefd, cmd));
}

/**
 * Processes heredoc (`<<`) redirections for all commands in the command list.
 *
 * Iterates through each command in `ms->cmd_lst`, checking if it has a 
 * heredoc delimiter (`heredoc_del`). If so, it calls process_heredoc.
 *
 * If any heredoc processing fails, `ms->exit_code` is set to EXIT_FAILURE.
 *
 * @param ms Pointer to the global Minishell structure.
 * @return EXIT_SUCCESS (failure is tracked in `ms->exit_code`).
 */
int	process_all_heredocs(t_minishell *ms)
{
	t_cmd	*cmd;
	int		exit_code;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		if (cmd->heredoc->delimiter)
		{
			exit_code = process_heredoc(cmd, ms);
			if (exit_code != EXIT_SUCCESS)
			{
				ms->exit_code = exit_code;
				return (EXIT_FAILURE);
			}
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}