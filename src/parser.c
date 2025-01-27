
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

t_node	*create_node(void *cmd)
{
	t_node	*node;

	t_node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(t_cmd));
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	node->cmd->args = NULL;
	node->cmd->infile = NULL;
	node->cmd->outfile = NULL;
	return (node);
}

void	parse_command(char *group, t_cmd *cmd)
{
	char	**tokens;
	int		i;
	int		args_count;

	if (!group || !cmd)
		return;
	tokens = tokenizer(group);
	if (!tokens)
		return;
	cmd->args = malloc(sizeof(char *) * (ft_strlen(group) + 1));
	cmd->infile = NULL;
	cmd->outfile = NULL;
	args_count = 0;
	i = 0;
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
			args_count++;
		}
	cmd->args[args_count] = '\0';
	i = 0;
	while (tokens && tokens[i])
	{
		free(tokens[i]);
		i++;

	}
	free(tokens);
}
