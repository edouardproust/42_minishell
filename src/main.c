#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_cmd	*cmd_lst;

	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO (Ed) Deal with non-interactive mode
	input = readline("minishell> ");
	if (!input)
		return (EXIT_FAILURE);
	cmd_lst = create_cmd_lst(input);
	free(input);
	if (!cmd_lst)
		return (EXIT_FAILURE);
	//debug_cmd_lst(cmd_lst); // DEBUG
	execute_cmd_lst(&cmd_lst, envp);
	free_cmd_lst(&cmd_lst);
	return (EXIT_SUCCESS);
}
