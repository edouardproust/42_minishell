#include "minishell.h"
//helper functions for the parser
void	handle_input_redirection(t_cmd *current_cmd, t_token **tokens)
{
	if ((*tokens)->next)
	{
		printf("Handling Input Redirection\n");
		if (current_cmd->infile)
			free(current_cmd->infile);
		current_cmd->infile = ft_strdup((*tokens)->next->value);
		printf("Input Redirection: infile = %s\n", current_cmd->infile);
		*tokens = (*tokens)->next;
	}
}

void    handle_output_redirection(t_cmd *current_cmd, t_token **tokens)
{
	if ((*tokens)->next)
	{
		printf("Handling Output Redirection\n");
		if (current_cmd->outfile)
			free(current_cmd->outfile);
		current_cmd->outfile = ft_strdup((*tokens)->next->value);
		printf("Output Redirection: outfile = %s\n", current_cmd->outfile); 
		*tokens = (*tokens)->next;
	}
}

void	handle_word(t_cmd *current_cmd, t_token *tokens)
{
	add_arg_to_cmd(current_cmd, tokens->value);
}

void	handle_pipe(t_cmd **current_cmd)
{
	if (!(*current_cmd)->args || !(*current_cmd)->args[0])
			return ;
	(*current_cmd)->next = cmd_new();
	*current_cmd = (*current_cmd)->next;
}
