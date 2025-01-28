#include "minishell.h"

void	execute_command(t_cmd *cmd, int *pipefd, int haspipe)
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
	pid_t	child_pid;
	int		status;

	exec_print_cmd_input(input); // TODO (E) remove (testing)

	while (input != NULL)
	{
		if (input->next !== NULL)
		{
			if (pipe(pipefd) == -1)
				ft_perror("pipe"); // TODO (E) Leaks
			//child_pid = execute_command(??);
			//close(pipefd[??]);
		}
		else
		//	child_pid = execute_command(???);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_perror("child status"); // TODO leaks
		input = input->next;
	}
	(void)list;
	return (EXIT_SUCCESS);
}
