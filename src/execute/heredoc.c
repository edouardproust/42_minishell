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

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (ft_free(1, &line), EXIT_FAILURE);
		if (ft_strcmp(line, cmd->heredoc_del) == 0)
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
	ft_close(&pipefd[0]);
	ft_signal(SIGINT, SIG_DFL);
	if (read_heredoc(cmd, pipefd[1]) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	flush_fds();
	free_minishell(&ms);
	exit(EXIT_SUCCESS);
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
		return (E_SIGBASE + WTERMSIG(status));
	}
	cmd->heredoc_fd = pipefd[0];
	if (cmd->heredoc_fd != -1)
	{
		cmd->fdin = cmd->heredoc_fd;
		cmd->heredoc_fd = -1;
		if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_FAILURE)
			return (put_error("heredoc: dup2"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Manages heredoc processing using pipe communication.
 * 
 * @param cmd Command structure with heredoc details
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on pipe/fork error
 */
int	process_heredoc(t_cmd *cmd, t_minishell *ms)
{
	int		pipefd[2];
	pid_t	pid;

	if (!cmd->heredoc_del)
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
	ms->exit_code = handle_parent_process(pid, pipefd, cmd);
	return (EXIT_SUCCESS);
}
