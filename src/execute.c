#include "minishell.h"

void	execute_command(t_cmd *cmd, int *pipefd)
{
	if (cmd->infile != NULL)
	{
		if (access(cmd->infile) == -1)
			ft_perror("access"); // TODO leaks
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
}

int	execute_input(t_node *input)
{
	int		*pipefd;
	pid_t	pid;
	int		status;

	exec_print_cmd_input(input); // TODO (E) remove (testing)

	while (input != NULL)
	{
		if (input->next !== NULL)
		{
			if (pipe(pipefd) == -1)
				ft_perror("pipe"); // TODO (E) Leaks
			if (pid == -1)
				ft_perror("fork"); // TODO (E) Leaks
			if (pid == 0)
				exec_command(input, pipefd);
			else
			{
				waitpid(pid, &status, 0); // TODO (E) Protect inside a loop with status checks
			}
		}
		input = input->next;
	}
	(void)list;
	return (EXIT_SUCCESS);
}
