
#include "minishell.h"

char	**tokenizer(char *input)
{
	char	**tokens;
	
	if (!input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}

//Only handle <, > redirections for now to test
//TO DO (F) single and double quotes handling, pipes (|), <<, >>
void	parse_token(char **tokens, t_cmd *cmd)
{
	int	i;
	int	args_count;

	i = 0;
	args_count = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<", 1) == 0)
		{
			i++;
			if (tokens[i])
				cmd->infile = ft_strdup(tokens[i]);
		}
		else if (ft_strncmp(tokens[i], ">", 1) == 0)
		{
			i++;
			if (tokens[i])
				cmd->outfile = ft_strdup(tokens[i]);
		}
		else
		{
			cmd->args[args_count] = ft_strdup(tokens[i]);
			if (!cmd->args[args_count])
				return;
			args_count++;
		}
		i++;
	}
	cmd->args[args_count] = NULL;
}

void	parse_command(char *group, t_cmd *cmd)
{
	char	**tokens;
	int		i;
	int		token_count;

	if (!group || !cmd)
		return;
	tokens = tokenizer(group);
	if (!tokens)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	token_count = 0;
	while (tokens[token_count])
		token_count++;
	cmd->args = malloc(sizeof(char *) * (token_count + 1));
	if (cmd->args)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		return ;
	}
	parse_token(tokens, cmd);
	i = 0;
	parse_token(tokens, cmd);
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
