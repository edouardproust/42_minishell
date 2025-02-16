#include "minishell.h"

/*Hndles the '|' (pipe) token by creating a new command.
 *
 * If the pipe is followed by another pipe or is at the end of the input,
 * an error is triggered.
 *
 * - Advances the current token to the next valid command.
 * - Links the new command to the existing list.
 */
void	handle_pipe(t_parse *parse)
{
	if (!parse->current_token->next || parse->current_token->next->type == TOKEN_PIPE)
		exit_parsing(parse, "syntax error near unexpected token `|'");
	parse->current_token = parse->current_token->next;
	parse->current_cmd->next = cmd_new(parse->current_cmd);
	if (!parse->current_cmd->next)
		exit_parsing(parse, "malloc error");
	parse->current_cmd = parse->current_cmd->next;
}

void	handle_input_redirection(t_parse *parse)
{
	if (!parse->current_token->next || parse->current_token->next->type != TOKEN_WORD)
		exit_parsing(parse, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &parse->current_cmd->infile);
	parse->current_cmd->infile = ft_strdup(parse->current_token->next->value);
	if (!parse->current_cmd->infile)
		exit_parsing(parse, "malloc error");
	parse->current_token = parse->current_token->next;
}

void	handle_output_redirection(t_parse *parse)
{
	if (!parse->current_token->next || parse->current_token->next->type != TOKEN_WORD)
		exit_parsing(parse, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &parse->current_cmd->outfile);
	parse->current_cmd->outfile = ft_strdup(parse->current_token->next->value);
	if (!parse->current_cmd->outfile)
		exit_parsing(parse, "malloc error");
	parse->current_token = parse->current_token->next;
}

void	handle_word(t_parse *parse)
{
	char	*arg_copy;

	arg_copy = ft_strdup(parse->current_token->value);
	if (!arg_copy)
		exit_parsing(parse, "malloc error"); 
	add_arg_to_cmd(parse->current_cmd, arg_copy);
}
