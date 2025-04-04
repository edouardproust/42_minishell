/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:42 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:33:54 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles child process for heredoc input collection.
 *
 * @param pipefd Pipe file descriptors array
 * @param cmd Command structure containing heredoc details
 * @param ms Struct containing data on the program
 */
static void	handle_child_process(int *pipefd, t_infile *infile, t_minishell *ms)
{
	int	exit_code;

	ft_signal(SIGINT, heredoc_sigint_handler);
	ft_close(&pipefd[0]);
	exit_code = read_heredoc(infile, pipefd[1], ms);
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
static int	handle_parent_process(int pid, int *pipefd, t_infile *infile)
{
	int	status;

	ft_signal(SIGINT, SIG_IGN);
	ft_close(&pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		ft_close(&pipefd[0]);
		if (WEXITSTATUS(status) > E_SIGBASE)
		{
			ft_close(&pipefd[0]);
			infile->hdoc_fd = -1;
		}
		return (WEXITSTATUS(status));
	}
	infile->hdoc_fd = pipefd[0];
	return (EXIT_SUCCESS);
}

/**
 * Manages heredoc processing using pipe communication.
 *
 * @param cmd Command structure with heredoc details
 * @param ms Struct containing data on the program
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on pipe/fork error
 */
static int	process_heredoc(t_infile *infile, t_minishell *ms)
{
	int		pipefd[2];
	pid_t	pid;

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
		handle_child_process(pipefd, infile, ms);
	return (handle_parent_process(pid, pipefd, infile));
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
	int		i;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		i = 0;
		while (cmd->infiles && cmd->infiles[i])
		{
			if (cmd->infiles[i]->is_heredoc)
			{
				exit_code = process_heredoc(cmd->infiles[i], ms);
				if (exit_code != EXIT_SUCCESS)
				{
					ms->exit_code = exit_code;
					return (exit_code);
				}
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
