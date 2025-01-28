#include "minishell.h"

void	parse_arguments(char **tokens, t_node **args_list)
{
	int		i;
	t_node	*new_node;
	t_node	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<", 2) == 0 || ft_strncmp(tokens[i], ">", 2) == 0)
		{
			i = i + 2; //we need to skip redirections here and the next target file
			continue ;
		}
		new_node = create_node(NULL);
		if (!new_node)
			return ;
		populate_node(new_node, tokens[i]);
		if (!(*args_list))
			*args_list = new_node;
		else
		{
			tmp = *args_list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_node;
		}
		i++;
	}
}

//Only handle <, > redirections for now to test
//TO DO (F) single and double quotes handling, pipes (|), <<, >>
void	parse_redirections(char **tokens, t_node *node)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<", 2) == 0)
		{
			free(node->cmd->infile);
			node->cmd->infile = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else if (ft_strncmp(tokens[i], ">", 2) == 0)
		{
			free(node->cmd->outfile);
			node->cmd->outfile = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else
			i++;
	}
}

void	parse_command(char *input, t_cmd **cmd)
{
	char	**tokens;
	int		i;

	if (!input || !cmd)
		return;
	tokens = tokenizer(input);
	if (!tokens)
		return;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	parse_redirections(tokens, cmd);
	parse_arguments(tokens, cmd);
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
