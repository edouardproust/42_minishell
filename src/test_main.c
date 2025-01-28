#include "minishell.h"
#include <stdio.h>
//This is to test parsing only
int	main(int argc, char **argv)
{
	char	*input;
	char	**tokens;
	t_cmd	*args_list;
	int		i;

	(void)argc;
	(void)argv;
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
		args_list = NULL;
		tokens = tokenizer(input);
		if (!tokens)
		{
			free(input);
			continue;
		}
		parse_command(input, &args_list);
		printf("Parsed command:\n");
		i = 0;
		if (args_list)
		{
			while (args_list)
			{
				if (args_list->cmd->args)
				{
					printf(" Arguments:\n");
					i = 0;
					while (args_lst->cmd->args[i])
					{
						printf("   [%d]: %s\n", i, args_list->cmd->args[i]);
						i++;
					}
				}
				else
					printf(" No arguments found.\n");
				if (args_list->cmd->infile)
					printf(" Input file: %s\n", args_list->cmd->infile);
				else
					printf(" No input redirection.\n");
				if (args_list->cmd->outfile)
					printf(" Output file: %s\n", args_list->cmd->outfile);
				else
					printf(" No output redirection.\n");
				args_list = args_list->next;
			}
		}	
		free(input);
		free(tokens);
		free(args_list->cmd->args);
		free(args_list->cmd->infile);
		free(args_list->cmd->outfile);
	}
    return (EXIT_SUCCESS);
}
