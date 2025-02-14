#include "minishell.h"

int	do_export(char **args, t_minishell *minishell)
{
	(void)args;
	(void)minishell;
	return (EXIT_SUCCESS);
	
	// if arg[1] already in envvars
	//		envvars_updatedone();
	// else
	//		envvars_new();
	// 		envvars_addoneback();
	// return update_envp(minishell->envp);
}
