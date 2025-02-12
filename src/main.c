#include "minishell.h"
# include "debug.h" // TODO: remove

int	main(int ac, char **av, char **envp)
{
	t_envvar	*env;
	//t_cmd		*cmd_lst;

	(void)av;
	//cmd_lst = NULL;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO: (Ed) Deal with non-interactive mode
	env = init_envvars(envp);
	//if (!env) TODO:
	if (DEBUG) // DEBUG
	{
		t_envvar *var1 = envvar_new("TEST=this:is:a:test"); // DEBUG
		t_envvar *var2 = envvar_new("VAR=var=OK"); // DEBUG
		envvar_addoneback(&env, var1); // DEBUG
		envvar_addoneback(&env, var2); // DEBUG
		t_envvar *var3 = envvar_findbyname(env, "TEST");
		envvar_deleteone(&env, var3);
		t_envvar *var4 = envvar_findbyname(env, "VAR");
		envvar_updateone(var4, "var=NO");
		debug_envvars(env);
		open_logfile("test/log");
	//	cmd_lst = create_cmd_lst();
	}
	else
		ft_printf("[TODO: Parsing]\n"); // TODO:
	//execute_cmd_lst(&cmd_lst, envp);
	//free_cmd_lst(&cmd_lst);
	free_envvar_lst(&env);
	if (DEBUG) // DEBUG
		close(g_logfd);
	return (EXIT_SUCCESS);
}
