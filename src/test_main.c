#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	t_token     *tokens; 
	t_cmd       *cmds; 
	
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
		tokens = tokenizer(input);
		printf("\n---- Tokenized Input ----\n");
		print_tokens(tokens);
		cmds = parse_tokens(tokens);
		printf("\n---- Parsed Commands ----\n");
		print_cmds(cmds);
		free_token_lst(&tokens);
		free_cmd_lst(&cmds);
		free(input);
	}
	return (EXIT_SUCCESS);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: '%s' (Type: %d)\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Command: ");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("%s ", cmd->args[i]);
				i++;
			}
		}
		printf("\nInfile: %s\n", cmd->infile ? cmd->infile : "(none)");
		printf("Outfile: %s\n", cmd->outfile ? cmd->outfile : "(none)");
		printf("----------------\n");
		cmd = cmd->next;
	}
}
