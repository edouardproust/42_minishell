#include "minishell.h"

t_pid	execute_command(t_cmd *cmd, int *pipefd)
{
	return (pid);
}

int	execute_input(t_node *input)
{
	int		*pipefd;
	int		in_fd;
	int		out_fd;
	pid_t	child_pid;
	int		status;

	exec_print_cmd_input(input); // TODO (E) remove (testing)

	while (input != NULL)
	{
		in_fd = STDIN_FILENO;
		out_fd = STDOUT_FILENO;
		if (input->cmd->pipe_after)
		{
			if (pipe(pipefd) == -1)
				ft_perror("pipe"); // TODO (E) Leaks
			out_fd = pipefd[1];
		}
		else
		{
			if (input->cmd->infile)
			{	
				// TODO update in_fd
			}
			if (input->cmd->outfile)
			{
				// TODO update out_fd based
			}
		}
		child_pid = execute_command(input->cmd, in_fd, out_fd);
		// prepare next command's in_fd
		if (input->cmd->pipe_after)
		{
			in_fd = pipefd[0];
			close(pipefd[1]);
		}
		waitpid(child_pid, &status, 0); // TODO check error
		// prev_pie_in > new_pipe_out
		input = input->next;
	}
	return (EXIT_SUCCESS);
}
