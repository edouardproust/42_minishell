#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_cmd	*cmd_lst; 
	
	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			ft_printf("exit\n");
			ft_free_ptrs(1, &input);
			break ;
		}
		if (*input)
			add_history(input);
		cmd_lst = create_cmd_lst(input);
		if (cmd_lst)
		{
			free_cmd_lst(&cmd_lst);
			free(input);
			return (EXIT_FAILURE);
		}
		free(input);
	}
	return (EXIT_SUCCESS);
}
