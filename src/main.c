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
	minishell->input_line = 0;
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
 * Reads input from the user and handles signal-related behavior.
 *
 * - Prompts the user for input using `readline`.
 * - Adds the input to the command history.
 * - Handles SIGINT signals and updates the exit code accordingly.
 * - Exits the minishell gracefully if EOF (Ctrl+D) is received.
 *
 * @param ms Pointer to the minishell data structure.
 * @return void
 */
static void	set_input(t_minishell *ms)
{
	int	sig;

	set_errno(EXIT_SUCCESS);
	ms->input = readline("minishell$ ");
	add_history(ms->input);
	ms->input_line++;
	sig = get_and_reset_signal();
	if (sig == SIGINT)
		ms->exit_code = E_SIGBASE + SIGINT;
	if (!ms->input)
	{
		if (errno != EXIT_SUCCESS)
			put_error("readline");
		else
		{
			ft_printf("exit\n");
			exit_minishell(EXIT_SUCCESS, ms, NULL);
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
		return (put_error("no arguments allowed."), EXIT_FAILURE);
	ft_signal(SIGQUIT, SIG_IGN);
	ft_signal(SIGINT, rl_sigint_handler);
	minishell = init_minishell(envp);
	while (1)
	{
		set_input(minishell);
		init_cmd_lst(minishell);
		if (minishell->cmd_lst == NULL)
			continue ;
		ft_signal(SIGINT, exec_sigint_handler);
		execute_cmd_lst(minishell);
		free_cmd_lst(&minishell->cmd_lst);
		ft_signal(SIGINT, rl_sigint_handler);
	}
	free_minishell(&minishell);
	return (EXIT_SUCCESS);
}
