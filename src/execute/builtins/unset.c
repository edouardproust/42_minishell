#include "minishell.h"

int	do_unset(char **args, t_minishell *minishell)
{
	(void)args;
	(void)minishell;
	return (EXIT_SUCCESS);
	
	// envvars_findbyname(args[1]);
	// if is not found
	//		return (EXIT_SUCCESS)
	// else
	// 		envvars_deleteone();
	// return (update_envp(minishell->envp);
}
