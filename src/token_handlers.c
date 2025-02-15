#include "minishell.h"
//TODO (A) add fucntions for heredoc and append

void	handle_pipe(t_cmd **cmd_list_head, t_cmd **current_cmd, t_token **tokens_head, t_token **current_token)
{
	if (!(*current_token)->next || (*current_token)->next->type == TOKEN_PIPE)
		exit_parsing(cmd_list_head, tokens_head, "syntax error near unexpected token `|'");
	*current_token = (*current_token)->next;
	(*current_cmd)->next = cmd_new(*current_cmd);
	if (!(*current_cmd)->next)
		exit_parsing(cmd_list_head, tokens_head, "malloc error");
	*current_cmd = (*current_cmd)->next;
}

void	handle_input_redirection(t_cmd **cmd_list_head, t_token **tokens_head, t_cmd *current_cmd, t_token **current_token)
{
	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		exit_parsing(cmd_list_head, tokens_head, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &current_cmd->infile);
	current_cmd->infile = ft_strdup((*current_token)->next->value);
	if (!current_cmd->infile)
		exit_parsing(cmd_list_head, tokens_head, "malloc error");
	*current_token = (*current_token)->next;
}

void	handle_output_redirection(t_cmd **cmd_list_head, t_token **tokens_head, t_cmd *current_cmd, t_token **current_token)
{
	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		exit_parsing(cmd_list_head, tokens_head, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &current_cmd->outfile);
	current_cmd->outfile = ft_strdup((*current_token)->next->value);
	if (!current_cmd->outfile)
		exit_parsing(cmd_list_head, tokens_head, "malloc error");
	*current_token = (*current_token)->next;
}

void	handle_word(t_cmd **cmd_list_head, t_token **tokens_head, t_cmd *current_cmd, t_token *token)
{
	char	*arg_copy;

	arg_copy = ft_strdup(token->value);
	if (!arg_copy)
		exit_parsing(cmd_list_head, tokens_head, "malloc error"); 
	add_arg_to_cmd(current_cmd, arg_copy);
}
