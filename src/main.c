#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd *cmd_lst;

	(void)av;
	cmd_lst = NULL;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO (Ed) Deal with non-interactive mode
	if (DEBUG)
		cmd_lst = create_cmd_lst();
	else
		ft_printf("[TODO: Parsing]\n"); // TODO	
	execute_cmd_lst(&cmd_lst, envp);
	free_cmd_lst(&cmd_lst);
	return (EXIT_SUCCESS);
}
