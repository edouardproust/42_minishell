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

int	main(void)
{
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
	t_node *parsed_input = exec_init_struct(); // TODO: Remove (created for testing purpose)
	execute_input(parsed_input);

	return (EXIT_SUCCESS);
}
