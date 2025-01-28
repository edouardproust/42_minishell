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

void	populate_node(t_node *node, char *arg)
{
	if (!node || !arg)
		return ;
	node->cmd->args = malloc(sizeof(char *) * 2);
	if (!node->cmd->args)
		return ;
	node->cmd->args[0] = ft_strdup(arg);
	if (!node>cmd->args[0])
	{
		free(node->cmd->args);
		node->cmd->args = NULL;
		return ;
	}
	node->cmd->args[1] = NULL;
	node->cmd->infile = NULL;
	node->cmd->outffile = NULL;
}
