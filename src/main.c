#include "minishell.h"
# include "debug.h" // TODO: remove

int	main(int ac, char **av, char **envp)
{
	t_envvar	*env;
	t_cmd		*cmd_lst;

	(void)av;
	cmd_lst = NULL;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO: (Ed) Deal with non-interactive mode
	env = init_envvars(envp);
	//if (!env) TODO:
	if (DEBUG) // DEBUG
	{
		debug_envvars(env);
		open_logfile("test/log");
		cmd_lst = create_cmd_lst();
	}
	else
		ft_printf("[TODO: Parsing]\n"); // TODO:
	execute_cmd_lst(&cmd_lst, envp);
	free_cmd_lst(&cmd_lst);
	if (DEBUG) // DEBUG
		close(g_logfd);
	return (EXIT_SUCCESS);
}
