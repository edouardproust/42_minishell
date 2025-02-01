#include "minishell.h"
#include <stdio.h>

t_cmd	*create_cmd()
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int	i;
	int	count;
	char	**new_args;
	
	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arg;
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = create_cmd();
	current_cmd = cmd_list;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg_to_cmd(current_cmd, tokens->value);
		else if (tokens->type == TOKEN_REDIR_IN && tokens->next)
		{
			if (current_cmd->infile)
				free(current_cmd->infile);
			current_cmd->infile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_REDIR_OUT && tokens->next)
		{
			if (current_cmd->outfile)
				free(current_cmd->outfile);
			current_cmd->outfile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			if (!current_cmd->args || !current_cmd->args[0]) //check for empty commands
				return (NULL);
			current_cmd->next = create_cmd(); //create new cmd
			current_cmd = current_cmd->next; //move to new cmd
		}
		tokens = tokens->next;
	}
	return (cmd_list);
}
