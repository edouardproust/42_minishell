
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	char	*input;
	
	while (1)
	{	
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break;
		}
//		if (ft_strlen(input) > 0)
//			add_history(input);
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			ft_printf("exit\n");
			break;
		}
	}
	free(input);
}
