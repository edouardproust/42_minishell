#include "minishell.h"

void	execute_command(t_cmd *cmd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror("fork"); // TODO (E) Leaks
	if (pipefd != NULL)
	{
		dup2(); // TODO (E) check error
		close(pipefd[1]);
	}
	if (cmd->infile != NULL)
	{
		if (access(cmd->infile) == -1)
			ft_perror("access"); // TODO (E) leaks
		// open(); // TODO
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != NULL)
	{

	}
}

int	execute_input(t_node *input)
{
	int		*pipefd;
	pid_t	child_pid;
	int		status;

	exec_print_cmd_input(input); // TODO (E) remove (testing)

	while (input != NULL)
	{
		if (input->cmd->pipe_after)
		{
			if (pipe(pipefd) == -1)
				ft_perror("pipe"); // TODO (E) Leaks
			child_pid = execute_command(input->cmd, pipefd);
		}
		else
			child_pid = execute_command(input->cmd, NULL);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_perror("child status"); // TODO leaks
		input = input->next;
	}
	(void)list;
	return (EXIT_SUCCESS);
}
