#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
        input = readline("minishell$ ");
		if (!input)
			break;
        if (ft_strncmp(input, "exit", 5) == 0)
        {
            ft_printf("exit\n");
            ft_free_ptrs(1, &input);
            break;
		}
		if (*input)
        	add_history(input);
        free(input);
		cmd.args = NULL;
		cmd.infile = NULL;
		cmd.outfile = NULL;
		tokens = tokenizer(input);
		parse_command(input, &cmd);
		execute(&cmd);
		free(input);
//		free(cmd.infile);
//		free(cmd.outfile);
	}
    return (EXIT_SUCCESS);
}
