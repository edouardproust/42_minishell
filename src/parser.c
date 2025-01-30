#include "minishell.h"
#include <stdio.h>
//fills cmd_>args with remaining arguments
void	parse_arguments(char **tokens, t_node *node)
{
	int	i;
	int	j;
	int	count;
	char	**new_args;

	if (!node || !tokens || !node->cmd)
		return;
	if (!node->cmd->args)
	{
		node->cmd->args = malloc(sizeof(char *));
		if (!node->cmd->args)
			return ;
		node->cmd->args[0] = NULL;
	}
	i = 1;
	count = 0;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 2) != 0)
	{
		if (ft_strncmp(tokens[i], "<", 2) == 0 || ft_strncmp(tokens[i], ">", 2) == 0)
		{
			i = i + 2; //we want to skip the redirection and the filename
			continue ;
		}
		while (node->cmd->args[count] != NULL)
			count++;
		new_args = malloc(sizeof(char *) * (count + 2)); //1 for new arg, 1 for NULL
		if (!new_args)
			return ;
		j = 0;
		while (j < count)
		{
			new_args[j] = node->cmd->args[j];
			j++;
		}
		new_args[count] = ft_strdup(tokens[i]);
		new_args[count + 1] = NULL;
		free(node->cmd->args);
		node->cmd->args = new_args;
		i++;
	}
}

//Only handle <, > redirections for now to test, we set infile and outfile atm
void	parse_redirections(char **tokens, t_node *node)
{
	int	i;
	
	if (!node || !tokens || !node->cmd)
	{
		printf("Error: Null node or command structure in parse_redirections\n");
		return ;
	}
	i = 0;
	while (tokens[i])
	{
		printf("Token[%d]: %s\n", i, tokens[i]);
		if (tokens[i + 1])
		{
			if (ft_strncmp(tokens[i], "<", 2) == 0)
			{
				if (node->cmd->infile)
					free(node->cmd->infile);
				node->cmd->infile = ft_strdup(tokens[i + 1]);
				i = i + 2;
			}
			else if (ft_strncmp(tokens[i], ">", 2) == 0)
			{
				printf("Parsing > redirection. Setting outfile...\n");
				if (node->cmd->outfile)
					free(node->cmd->outfile);
				node->cmd->outfile = ft_strdup(tokens[i + 1]);
				printf("Set outfile: %s\n", node->cmd->outfile);
				i = i + 2;
			}
		}
		i++;
	}
}
//creates a node for each command separated by |
void	parse_command(char *input, t_node **args_list)
{
	char	**tokens;
	int		i;
	t_node	*current_node;
	t_node	*new_node;

	if (!input || !args_list)
		return;
	tokens = tokenizer(input);
	if (!tokens)
		return;
	i = 0;
//	current_node = NULL;
//	new_node = NULL;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			i++;
			continue;
		}
		new_node = create_node();
		if (!new_node)
			break ;
		populate_node(new_node, tokens[i]); //initializes the first argument in cmd->args
		parse_arguments(tokens + i + 1, new_node); //we parse the ramaining arguments to cmd->args
		parse_redirections(tokens + i + 1, new_node);
		if (!(*args_list == NULL))
			*args_list = new_node;
		else
		{
			current_node = *args_list;
			while (current_node->next)
				current_node = current_node->next;
			current_node->next = new_node;
		}
		i++;
	}
	free(tokens);
}
