#include "minishell.h"
# include "debug.h" // TODO: remove

static	t_minishell	*init_minishell(char **envp)
{
	t_minishell *minishell;
	
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit_minishell(EXIT_FAILURE, NULL, "failed to initialize");
	minishell->cmd_lst = NULL;
	minishell->envp = ft_matrix_dup(envp);
	if (!minishell->envp)
		exit_minishell(EXIT_FAILURE, &minishell, "failed to copy environment");
	minishell->envvar_lst = init_envvars(minishell);
	if (!minishell->envvar_lst)
		exit_minishell(EXIT_FAILURE, &minishell,
			"failed to initialize environment variables");
	return (minishell);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell *minishell;

	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO: (Ed) Deal with non-interactive mode
	minishell = init_minishell(envp);
	if (DEBUG) // DEBUG
	{
		debug_envvars(minishell->envvar_lst);
		open_logfile("test/log");
		minishell->cmd_lst = create_cmd_lst();
	}
	else
		ft_printf("[TODO: Parsing]\n"); // TODO:
	execute_cmd_lst(&minishell);
	free_minishell(&minishell);
	if (DEBUG) // DEBUG
		close(g_logfd);
	return (EXIT_SUCCESS);
}
