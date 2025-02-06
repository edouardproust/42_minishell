#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO (Ed) Deal with non-interactive mode
	t_cmd *cmd_lst = create_cmd_lst(); // DEBUG
	execute_cmd_lst(&cmd_lst, envp);
	free_cmd_lst(&cmd_lst);
	return (EXIT_SUCCESS);
}
