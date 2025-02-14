#include "minishell.h"
//TODO (A) add fucntions for heredoc and append
void	handle_input_redirection(t_cmd *current_cmd, t_token **tokens)
{
	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		exit_parsing(NULL, tokens, "syntax error near unexpected token `newline'");
	if (current_cmd->infile)
		free(current_cmd->infile);
	current_cmd->infile = ft_strdup((*tokens)->next->value);
	if (!current_cmd->infile)
		return ;
	*tokens = (*tokens)->next;
}

void    handle_output_redirection(t_cmd *current_cmd, t_token **tokens)
{
	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		exit_parsing(NULL, tokens, "syntax error near unexpected token `newline'");
	if (current_cmd->outfile)
		free(current_cmd->outfile);
	current_cmd->outfile = ft_strdup((*tokens)->next->value);
	if (!current_cmd->outfile)
		return ;
	*tokens = (*tokens)->next;
}

void	handle_word(t_cmd *current_cmd, t_token *tokens)
{
	add_arg_to_cmd(current_cmd, tokens->value);
}

void	handle_pipe(t_cmd **current_cmd, t_token **tokens)
{
	if (!(*tokens)->next || (*tokens)->next->type == TOKEN_PIPE)
		exit_parsing(NULL, tokens, "syntax error near unexpected token `|'");
	*tokens = (*tokens)->next;
	(*current_cmd)->next = cmd_new(*current_cmd);
	*current_cmd = (*current_cmd)->next;
}

