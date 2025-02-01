#include "minishell.h"

t_node	*create_node(void)
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
	node->cmd->outfile = NULL;
	node->next = NULL;
	return (node);
}

void	populate_node(t_node *node, char *arg)
{
	if (!node || !arg)
		return ;
//	node->cmd = malloc(sizeof(t_cmd));
//	if (!node->cmd)
//		return ;
//	init_cmd_struct(node->cmd);
	node->cmd->args = malloc(sizeof(char *) * 2);
	if (!node->cmd->args)
	{
		printf("Error: Failed to allocate memory for args.\n");
		return ;
	}
	node->cmd->args[0] = ft_strdup(arg);
	node->cmd->args[1] = NULL;
//	node->cmd->infile = NULL;
//	node->cmd->outfile = NULL;
	printf("populate_node: args[0]: %s\n", node->cmd->args[0]);
}

void	free_nodes(t_node *node)
{
	int	i;
	
	if (!node)
		return;
	free_nodes(node->next);
	if (node->cmd)
	{
		if (node->cmd->args)
		{
			i = 0;
			while (node->cmd->args[i])
			{
				free(node->cmd->args[i]);
				i++;
			}
			free(node->cmd->args);
		}
		free(node->cmd->infile);
		free(node->cmd->outfile);
//		if (node->cmd->fdin > 0)
//			close(node->cmd->fdin);
//		if (node->cmd->fdout > 0)
//			close(node->cmd->fdout);
		free(node->cmd);
	}
	free(node);
}
