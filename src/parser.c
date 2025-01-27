
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


