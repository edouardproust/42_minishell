#include "minishell.h"

/**
 * Inititalize the t_minishell struct containing global data on the program.
 * 
 * @param envp Array containing the env. variables on program startup
 * @return the t_minishell struct
 * @note Exit program on memory allocation failure.
 */
t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit_minishell(E_CRITICAL, NULL, "failed to initialize");
	minishell->input = NULL;
	minishell->token_lst = NULL;
	minishell->cmd_lst = NULL;
	minishell->exit_code = 0;
	minishell->envp = ft_matrix_dup(envp);
	if (!minishell->envp)
		exit_minishell(E_CRITICAL, minishell, "failed to copy environment");
	minishell->envvar_lst = init_envvars(minishell);
	if (!minishell->envvar_lst)
		exit_minishell(E_CRITICAL, minishell,
			"failed to initialize environment variables");
	return (minishell);
}

/**
 * Main - Get size of readline's leak
 * Run `valgrind ./minishell`
 *
int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("readline_test$ ");
		if (ft_strncmp("exit", input, 5) == 0)
		{
			ft_printf("exit\n");
			ft_free_ptrs(1, &input);
			exit(EXIT_SUCCESS);
		}
		ft_printf("input: \"%s\"\n", input);
		ft_free_ptrs(1, &input);
	}
	return (EXIT_SUCCESS);
}
*/

/**
 * Main - Debug version (skip readline to check leaks)
 *
int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;
	char		*input;

	(void)av;
	minishell = init_minishell(envp);
	input = "<test/infile tail -n +4 | grep a | sort | uniq -c | sort -nr \
		| head -n 3";
	init_cmd_lst(input, minishell);
	execute_cmd_lst(minishell);
	free_minishell(&minishell);
	return (EXIT_SUCCESS);
}
*/

static void	set_input(t_minishell *minishell)
{
	set_errno(EXIT_SUCCESS);
	minishell->input = readline("minishell$ ");
	if (!minishell->input)
	{
		if (errno != EXIT_SUCCESS)
			put_error("readline");
		else
		{
			ft_printf("exit\n");
			exit_minishell(EXIT_SUCCESS, minishell, NULL);
		}
	}
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

	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); //TODO Deal with non-interactive mode
	init_signal_handlers();
	minishell = init_minishell(envp);
	while (1)
	{
		set_input(minishell);
		init_cmd_lst(minishell);
		execute_cmd_lst(minishell);
		free_cmd_lst(&minishell->cmd_lst);
	}
	free_minishell(&minishell);
	return (EXIT_SUCCESS);
}