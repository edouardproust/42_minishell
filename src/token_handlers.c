#include "minishell.h"
/* 
 * Handles the pipe (`|`) token by creating a new command.
 * - Checks for syntax errors like consecutive pipes.
 * - Creates a new command for the next part of the pipeline.
 * @TODO Check malloc error message (for now on NULL)
 * 
 */
void	handle_pipe(t_minishell **minishell)
{
	if (!(*minishell)->current_token->next || (*minishell)->current_token->next->type == TOKEN_PIPE)
		exit_minishell(EXIT_FAILURE, minishell, "syntax error near unexpected token `|'");
	(*minishell)->current_cmd->next = cmd_new((*minishell)->current_cmd);
	if (!(*minishell)->current_cmd->next)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*minishell)->current_cmd = (*minishell)->current_cmd->next;
}
/* 
 * Handles input redirection (`<`) token by setting the infile for the current command.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's infile field.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_input_redirection(t_minishell **minishell)
{
	if (!(*minishell)->current_token->next || (*minishell)->current_token->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*minishell)->current_cmd->infile);
	(*minishell)->current_cmd->infile = ft_strdup((*minishell)->current_token->next->value);
	if (!(*minishell)->current_cmd->infile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*minishell)->current_token = (*minishell)->current_token->next;
}
/* 
 * Handles output redirection (`>`) token by setting the outfile for the current command.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's outfile field.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_output_redirection(t_minishell **minishell)
{
	if (!(*minishell)->current_token->next || (*minishell)->current_token->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell, "syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*minishell)->current_cmd->outfile);
	(*minishell)->current_cmd->outfile = ft_strdup((*minishell)->current_token->next->value);
	if (!(*minishell)->current_cmd->outfile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*minishell)->current_token = (*minishell)->current_token->next;
}
/* 
 * Handles a word token by copying its value and adding it to the current command's arguments.
 * - Duplicates the word and adds it to the args list of the current command.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_word(t_minishell **minishell)
{
	char	*arg_copy;

	arg_copy = ft_strdup((*minishell)->current_token->value);
	if (!arg_copy)
		exit_parsing(EXIT_FAILURE, minishell, NULL); 
	add_arg_to_cmd((*minishell)->current_cmd, arg_copy);
}
