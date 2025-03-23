/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust & fpapadak                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:30 by eproust           #+#    #+#             */
/*   Updated: 2025/02/16 20:07:31 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit_minishell(E_CRITICAL, NULL, "failed to initialize");
	ms->input = NULL;
	ms->token_lst = NULL;
	ms->cmd_lst = NULL;
	ms->exit_code = 0;
	ms->input_line = 0;
	ms->envp = ft_matrix_dup(envp);
	if (!ms->envp)
		exit_minishell(E_CRITICAL, ms, "failed to copy environment");
	ms->envvar_lst = init_envvars(ms);
	if (!ms->envvar_lst)
		exit_minishell(E_CRITICAL, ms,
			"failed to initialize environment variables");
	return (ms);
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
static int	set_input(t_minishell *ms)
{
	int	sig;

	set_errno(EXIT_SUCCESS);
	ms->input = readline(BLUE "minishell$ " RST);
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
			printf("exit\n");
			exit_minishell(ms->exit_code, ms, NULL);
		}
	}
	return (EXIT_SUCCESS);
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
	t_minishell	*ms;

	(void)av;
	if (ac > 1)
		return (put_error("no arguments allowed."), EXIT_FAILURE);
	ft_signal(SIGQUIT, SIG_IGN);
	ft_signal(SIGPIPE, SIG_IGN);
	ft_signal(SIGINT, rl_sigint_handler);
	ms = init_minishell(envp);
	while (1)
	{
		if (set_input(ms) == EXIT_FAILURE)
			continue ;
		init_cmd_lst(ms);
		if (ms->cmd_lst == NULL)
			continue ;
		ft_signal(SIGINT, exec_sigint_handler);
		execute_cmd_lst(ms);
		free_cmd_lst(&ms->cmd_lst);
		ft_signal(SIGINT, rl_sigint_handler);
	}
	free_minishell(&ms);
	return (EXIT_SUCCESS);
}
