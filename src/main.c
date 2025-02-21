#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd_lst;

	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO (Ed) Deal with non-interactive mode
//	char	*input = "\"'\"Hello\"'\"";
	char	*input = "";
	cmd_lst = init_cmd_lst(input);
	if (!cmd_lst)
		return (EXIT_FAILURE);
	//debug_cmd_lst(cmd_lst); // DEBUG
	execute_cmd_lst(&cmd_lst, envp);
	free_cmd_lst(&cmd_lst);
	return (EXIT_SUCCESS);
}
