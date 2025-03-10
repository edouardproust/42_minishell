#include "minishell.h"

/**
 * Main - Get size of readline's leak
 * Run `valgrind ./minishell`
 */
int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("readline_test$ ");
		add_history(input);
		if (ft_strncmp("exit", input, 5) == 0)
		{
			ft_printf("exit\n");
			ft_free(1, &input);
			break ;
		}
		ft_printf("input: \"%s\"\n", input);
		ft_free(1, &input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

/**
 * Main - Debug version (skip readline to check leaks)
 */
int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;
	char		*input;

	(void)av;
	minishell = init_minishell(envp);
	input = "<test/infile tail -n +4 | grep a | sort | uniq -c | sort -nr \
		| head -n 3";
	init_cmd_lst(minishell);
	execute_cmd_lst(minishell);
	free_minishell(&minishell);
	return (EXIT_SUCCESS);
}
