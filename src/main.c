#include "minishell.h"

/*
t_token	*tokenize(char *input)
{

}

t_ast_node	*parse(t_token *tokens)
{

}

int	execute(t_ast_node *ast)
{
	// Go throught the tree and create pipelines
	// Execute pipeline sub-commands + do needed redirections
		// check if is a bultin command
		// else use execve
}
*/

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac > 1)
		return (EXIT_FAILURE); // TODO (E) Deal with non-interactive mode
/*
	char	*input;

	while (1)
	{
		input = readline("minishell $");
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			ft_printf("exit\n");
			ft_free_ptrs(1, &input);
			break;
		}
		add_history(input);
		free(input);
	}
*/
	t_node *pinput = debug_init_pinput(); // TODO (E) Remove (created for testing purpose)
	//debug_pinput(pinput); // TODO DEBUG
	execute_input(&pinput, envp);
	free_pinput(&pinput);

	return (EXIT_SUCCESS);
}
