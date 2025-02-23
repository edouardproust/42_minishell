#include "minishell.h"

/**
 * Inititalize the t_minishell struct containing global data on the program.
 * 
 * @param envp Array containing the env. variables on program startup
 * @return the t_minishell struct
 * @note Exit program on memory allocation failure.
 */
static	t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit_minishell(EXIT_FAILURE, NULL, "failed to initialize");
	minishell->token_lst = NULL;
	minishell->cmd_lst = NULL;
	minishell->envp = ft_matrix_dup(envp);
	if (!minishell->envp)
		exit_minishell(EXIT_FAILURE, minishell, "failed to copy environment");
	minishell->envvar_lst = init_envvars(minishell);
	if (!minishell->envvar_lst)
		exit_minishell(EXIT_FAILURE, minishell,
			"failed to initialize environment variables");
	return (minishell);
}

/**
 * Minishell entry point.
 * 
 * @param ac Number of arguments passed to the program
 * @param av Array of the arguments passed to the program
 * @param envp Array containing the environment variables on program startup
 * @return EXIT_SUCCESS or EXIT_FAILURE 
 */
int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;
	char		*input;

	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); //TODO Deal with non-interactive mode
	minishell = init_minishell(envp);
//	input = "<test/infile tail -n +4 | grep a | sort | uniq -c | sort -nr | head -n 3";
	input = "'echo hello'";
	init_cmd_lst(input, minishell);
	execute_cmd_lst(minishell);
	free_minishell(&minishell);
	return (EXIT_SUCCESS);
}
