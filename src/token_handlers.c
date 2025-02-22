#include "minishell.h"
/* 
 * Handles the pipe (`|`) token by creating a new command.
 * - Checks for syntax errors like consecutive pipes.
 * - Creates a new command for the next part of the pipeline.
 */
void	handle_pipe(t_parse *parse)
{
	t_token	*token;

	token = parse->current_token;
	if (!token->next || token->next->type == TOKEN_PIPE)
		exit_parsing(parse, "syntax error near unexpected token `|'");
	parse->current_cmd->next = cmd_new(parse->current_cmd);
	if (!parse->current_cmd->next)
		exit_parsing(parse, NULL);
	parse->current_cmd = parse->current_cmd->next;
	parse->current_token = token->next;
}

/* 
 * Handles input redir (`<`) token by setting the infile for the current cmd.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's infile field.
 */
void	handle_redir_in(t_parse *parse)
{
	t_token	*token;

	token = parse->current_token;
	if (!token->next || token->next->type != TOKEN_WORD)
		exit_parsing(parse, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &parse->current_cmd->infile);
	parse->current_cmd->infile = ft_strdup(token->next->value);
	if (!parse->current_cmd->infile)
		exit_parsing(parse, NULL);
	parse->current_token = token->next->next;
}

/* 
 * Handles output redir (`>`) token by setting the outfile for the current cmd.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's outfile field.
 */
void	handle_redir_out(t_parse *parse)
{
	t_token	*token;

	token = parse->current_token;
	if (!token->next || token->next->type != TOKEN_WORD)
		exit_parsing(parse, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &parse->current_cmd->outfile);
	parse->current_cmd->outfile = ft_strdup(token->next->value);
	if (!parse->current_cmd->outfile)
		exit_parsing(parse, NULL);
	parse->current_token = token->next->next;
}

/* 
 * Handles a word token by copying its value 
 * and adding it to the current command's arguments.
 * - Duplicates the word and adds it to the args list of the current cmd.
 */
void	handle_word(t_parse *parse)
{
	t_token	*token;
	char	*arg_copy;

	token = parse->current_token;
	arg_copy = ft_strdup(token->value);
	if (!arg_copy)
		exit_parsing(parse, NULL);
	add_arg_to_cmd(parse->current_cmd, arg_copy);
	parse->current_token = token->next;
}
