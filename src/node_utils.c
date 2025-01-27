#include "minishell.h"

t_node	*create_node(void *cmd)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(t_cmd));
	if (!node->cmd)
		return (free(node), NULL);
	node->cmd->args = NULL;
	node->cmd->infile = NULL;
	node->cmd->outffile = NULL;
	return (node);
}
