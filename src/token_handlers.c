#include "minishell.h"
/* 
 * Handles the pipe (`|`) token by creating a new command.
 * - Checks for syntax errors like consecutive pipes.
 * - Creates a new command for the next part of the pipeline.
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
/* 
 * Handles input redirection (`<`) token by setting the infile for the current command.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's infile field.
 */
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
/* 
 * Handles output redirection (`>`) token by setting the outfile for the current command.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's outfile field.
 */
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
/* 
 * Handles a word token by copying its value and adding it to the current command's arguments.
 * - Duplicates the word and adds it to the args list of the current command.
 */
void	handle_word(t_parse *parse)
{
	char	*arg_copy;

	arg_copy = ft_strdup(parse->current_token->value);
	if (!arg_copy)
		exit_parsing(parse, "malloc error"); 
	add_arg_to_cmd(parse->current_cmd, arg_copy);
}
