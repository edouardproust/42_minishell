#include "minishell.h"
#include <stdio.h>

//This is to test parsing only
int	main(int argc, char **argv)
{
	char	*input;
	t_node	*args_list;
	t_node	*tmp;
	int	i;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
        	if (ft_strncmp(input, "exit", 5) == 0)
		{
            		ft_printf("exit\n");
            		ft_free_ptrs(1, &input);
            		break ;
		}
		if (*input)
        		add_history(input);
		args_list = NULL;
		parse_command(input, &args_list);
		free(input);
		tmp = args_list;
		i = 1;
		while (tmp)
		{
			printf("Command: %s\n", tmp->cmd->args[0]);
			while (tmp->cmd->args[i])
			{
				printf("  Arg[%d]: %s\n", i, tmp->cmd->args[i]);
				i++;
			}
			if (tmp->cmd->infile)
				printf("  Input file: %s\n", tmp->cmd->infile);
			if (tmp->cmd->outfile)
				printf("  Output file: %s\n", tmp->cmd->outfile);
			printf("\n");
			tmp = tmp->next;
		}	
		free_nodes(args_list);
	}
    return (EXIT_SUCCESS);
}
